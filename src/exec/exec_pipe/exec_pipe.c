/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:08:50 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/12 11:47:15 by eelissal         ###   ########lyon.fr   */
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

static void	dup_pipe_fds(int infd, int outfd, bool left)
{
	if (left == true)
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
static void	redirect_fds(t_exec * exec, int fd[2], int *infd, int *outfd, bool left)
{
	if (left == true)
	{
		*infd = exec->infd;
		if (exec->outfd != STDOUT_FILENO)
			*outfd = exec->outfd;
		else
			*outfd = fd[1];
		close(fd[0]);
	}
	else
	{
		if (exec->infd != STDIN_FILENO)
			*infd = exec->infd;
		else
			*infd = fd[0];
		*outfd = exec->outfd;
		close(fd[1]);
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

static void	handle_redirections(t_exec *exec, int fd[2], bool left)
{
	int		infd;
	int		outfd;

	redirect_fds(exec, fd, &infd, &outfd, left);
	dup_pipe_fds(infd, outfd, left);
}

int exec_pipe(t_exec *exec)
{
	int		fd[2];
	int		pid[2];
	t_ast	*current;
	int		ret;

	if (pipe(fd) == -1)
	{
		strerror(errno); //TODO to check again
		return (1);
	}
	current = exec->current;
	pid[0] = fork();
	if (pid[0] == -1)
		return (handle_fork_error(fd, "fork"));
	if (pid[0] == 0)
	{
		exec->current = exec->current->left;
		handle_redirections(exec, fd, true);
		if (exec->current->tag == AST_CMD)
			handle_pipe_process(exec);
		else if (exec->current->tag == AST_PIPE)
		{
			ret = exec_node(exec);
			free_exec(exec);
			exit(ret);
		}
		// while (exec->current->tag != AST_CMD)
		// 	ret = exec_redir(exec); //à revoir sinon les redirs vont continuer vers l'execution des commandes normales, et non des commandes en pipe
	}
	exec->current = current;
	pid[1] = fork();
	if (pid[1] == -1)
	{
		if (pid[0] > 0)
			waitpid(pid[0], NULL, 0);
		return (handle_fork_error(fd, "fork"));
	}
	if (pid[1] == 0)
	{
		exec->current = exec->current->right;
		handle_redirections(exec, fd, false);
		// while (exec->current->tag != AST_CMD)
		// 	ret = exec_redir(exec); //à revoir sinon les redirs vont continuer vers l'execution des commandes normales, et non des commandes en pipe
		if (exec->current->tag == AST_CMD)
			handle_pipe_process(exec);
		else if (exec->current->tag == AST_PIPE)
		{
			ret = exec_node(exec);
			free_exec(exec);
			exit(ret);
		}
	}
	exec->current = current;
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], &exec->shell->status, 0);
	if (pid[0] > 0)
		waitpid(pid[1], &exec->shell->status, 0);
	return (return_process(exec));
}
