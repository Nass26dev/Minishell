/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:08:50 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/12 15:37:42 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

static int	handle_fork_error(int pipefd[2], const char *msg)
{
	perror(msg);
	close(pipefd[0]);
	close(pipefd[1]);
	return (FAIL_FORK);
}

static void	dup_pipe_fds(int infd, int outfd, int fd)
{
	if (fd == 0)
	{
		dup2(outfd, STDOUT_FILENO);
		close (outfd);
		if (infd != STDIN_FILENO)
		{
			dup2(infd, STDIN_FILENO);
			close(infd);
		}
	}
	else
	{
		dup2(infd, STDIN_FILENO);
		close (infd);
		if (outfd != STDOUT_FILENO)
		{
			dup2(outfd, STDOUT_FILENO);
			close(outfd);
		}
	}
}

static void	redirect_fds(t_exec * exec, int pipefd[2], int *infd, int *outfd, int fd)
{
	if (fd == 0)
	{
		*infd = exec->infd;
		if (exec->outfd != STDOUT_FILENO)
			*outfd = exec->outfd;
		else
			*outfd = pipefd[1];
		close(pipefd[0]);
	}
	else
	{
		if (exec->infd != STDIN_FILENO)
			*infd = exec->infd;
		else
			*infd = pipefd[0];
		*outfd = exec->outfd;
		close(pipefd[1]);
	}
}

static void	handle_pipe_process(t_exec *exec)
{
	char	*cmd;
	int		ret;

	ret = cmd_is_valid(exec);
	if (ret != 0)
	{
		free_exec(exec);
		exit (ret);
	}
	ret = is_builtin(exec);
	if (ret >= 0 && ret < 7)
		exit(exec_builtin(exec, ret));
	else
	{
		is_extern_cmd(exec, &cmd);
		exec_extern_cmd(exec, cmd);
	}
}

static void	handle_redirections(t_exec *exec, int pipefd[2], int fd)
{
	int		infd;
	int		outfd;

	redirect_fds(exec, pipefd, &infd, &outfd, fd);
	dup_pipe_fds(infd, outfd, fd);
}

static t_exec	*exec_redir_pipe(t_exec *exec)
{
	int	ret;
	
	if (exec->current->tag == AST_REDIR_IN)
		ret = handle_redir_in(exec);
	else if (exec->current->tag == AST_HEREDOC)
		ret = handle_heredoc(exec);
	else if (exec->current->tag == AST_REDIR_OUT)
		ret = handle_redir_out(exec);
	else if (exec->current->tag == AST_APPEND)
		ret = handle_append(exec);
	exec->current = exec->current->left;
	return (exec);
}

static int	exec_pipe_fork(t_exec *exec, int pipefd[2], int pid[2], int fd)
{
	int	ret;
	
	while (exec->current->tag >= AST_REDIR_IN && exec->current->tag <= AST_APPEND)
		exec = exec_redir_pipe(exec);
	pid[fd] = fork();
	if (pid[fd] == -1)
	{
		if (fd == 1 && pid[0] > 0)
			waitpid(pid[0], NULL, 0);
		return (handle_fork_error(pipefd, "fork"));
	}
	if (pid[fd] == 0)
	{
		handle_redirections(exec, pipefd, fd);
		if (exec->current->tag == AST_CMD)
			handle_pipe_process(exec);
		else if (fd == 0 && exec->current->tag == AST_PIPE)
		{
			ret = exec_node(exec);
			free_exec(exec);
			exit(ret);
		}
	}
	return (0);
}

int exec_pipe(t_exec *exec)
{
	int		pipefd[2];
	int		pid[2];
	t_ast	*current;

	if (pipe(pipefd) == -1)
	{
		strerror(errno); //TODO to check again
		return (1);
	}
	current = exec->current;
	exec->current = exec->current->left;
	if (exec_pipe_fork(exec, pipefd, pid, 0) != 0)
		return (FAIL_FORK);
	// while (exec->current->tag >= AST_REDIR_IN && exec->current->tag <= AST_APPEND)
	// 	exec = exec_redir_pipe(exec);
	// pid[0] = fork();
	// if (pid[0] == -1)
	// 	return (handle_fork_error(fd, "fork"));
	// if (pid[0] == 0)
	// {
	// 	handle_redirections(exec, fd, true);
	// 	if (exec->current->tag == AST_CMD)
	// 		handle_pipe_process(exec);
	// 	else if (exec->current->tag == AST_PIPE)
	// 	{
	// 		ret = exec_node(exec);
	// 		free_exec(exec);
	// 		exit(ret);
	// 	}
	// }
	exec->current = current;
	exec->current = exec->current->right;
	if (exec_pipe_fork(exec, pipefd, pid, 1) != 0)
		return (FAIL_FORK);
	// while (exec->current->tag >= AST_REDIR_IN && exec->current->tag <= AST_APPEND)
	// 	exec = exec_redir_pipe(exec);
	// pid[1] = fork();
	// if (pid[1] == -1)
	// {
	// 	if (pid[0] > 0)
	// 		waitpid(pid[0], NULL, 0);
	// 	return (handle_fork_error(fd, "fork"));
	// }
	// if (pid[1] == 0)
	// {
	// 	handle_redirections(exec, fd, false);
	// 	if (exec->current->tag == AST_CMD)
	// 		handle_pipe_process(exec);
	// 	else if (exec->current->tag == AST_PIPE)
	// 	{
	// 		ret = exec_node(exec);
	// 		free_exec(exec);
	// 		exit(ret);
	// 	}
	// }
	exec->current = current;
	close(pipefd[0]);
	close(pipefd[1]);
	close_fds(exec);
	waitpid(pid[0], &exec->shell->status, 0);
	if (pid[0] > 0)
		waitpid(pid[1], &exec->shell->status, 0);
	return (return_process(exec));
}
