/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:08:50 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/11 20:46:21 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

// static void	dup_infds(t_exec *exec, int pipefd[2])
// {
// 	close(pipefd[1]);
// 	if (exec->infd != STDIN_FILENO)
// 	{
// 		dup2(exec->infd, STDIN_FILENO);
// 		close(exec->infd);
// 	}
// 	else
// 		dup2(pipefd[0], STDIN_FILENO);
// 	close(pipefd[0]);
// }

// static void	dup_outfds(t_exec *exec, int pipefd[2])
// {
// 	close(pipefd[0]);
// 	if (exec->outfd != STDOUT_FILENO)
// 	{
// 		dup2(exec->outfd, STDOUT_FILENO);
// 		close(exec->outfd);
// 	}
// 	else
// 		dup2(pipefd[1], STDOUT_FILENO);
// 	close(pipefd[1]);
// }

// static void	handle_pipe_process(t_exec *exec, int pipefd[2], bool left)
// {
// 	char	*cmd;
// 	int		ret;

// 	if (left == true)
// 		exec->current = exec->current->left;
// 	else
// 		exec->current = exec->current->right;
// 	ret = cmd_is_valid(exec);
// 	if (ret != 0)
// 	{
// 		free_exec(exec);
// 		exit (ret);
// 	}
// 	if (left == true)
// 		dup_outfds(exec, pipefd);
// 	else
// 		dup_infds(exec, pipefd);
// 	ret = is_builtin(exec);
// 	if (ret >= 0 && ret < 7)
// 		exit(exec_builtin(exec, ret));
// 	else
// 	{
// 		is_extern_cmd(exec, &cmd);
// 		exec_extern_cmd(exec, cmd);
// 	}
// }

// static int	handle_fork_error(int pipefd[2], const char *msg)
// {
// 	perror(msg);
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	return (FAIL_FORK);
// }

// int	exec_pipe(t_exec *exec)
// {
// 	int	pipefd[2];
// 	int	pid[2];

// 	if (pipe(pipefd) == -1)
// 	{
// 		strerror(errno); //TODO to check again
// 		return (1);
// 	}
// 	pid[0] = fork();
// 	if (pid[0] == -1)
// 		return (handle_fork_error(pipefd, "fork"));
// 	if (pid[0] == 0)
// 		handle_pipe_process(exec, pipefd, true);
// 	pid[1] = fork();
// 	if (pid[1] == -1)
// 		return (handle_fork_error(pipefd, "fork"));
// 	if (pid[1] == 0)
// 		handle_pipe_process(exec, pipefd, false);
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	waitpid(pid[0], &exec->shell->status, 0);
// 	if (pid[0] > 0)
// 		waitpid(pid[1], &exec->shell->status, 0);
// 	return (return_process(exec));
// }

static void	dup_fds(t_exec *exec, int infd, int outfd, bool left)
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
static void	redirect_fds(t_exec *exec, int fd[2], int *infd, int *outfd, bool left)
{
	if (left == true)
	{
		*infd = exec->infd;
		if (exec->outfd != STDOUT_FILENO)
			*outfd = exec->outfd;
		else
			*outfd = fd[0];
		close(fd[1]);
	}
	else
	{
		if (exec->infd != STDIN_FILENO)
			*infd = exec->infd;
		else
			*infd = fd[1];
		*outfd = exec->outfd;
		close(fd[0]);
	}
}
static void	handle_pipe_process(t_exec *exec, int fd[2], bool left)
{
	char	*cmd;
	int		ret;
	int		infd;
	int		outfd;

	if (left == true)
		exec->current = exec->current->left;
	else
		exec->current = exec->current->right;
	redirect_fds(exec, fd, &infd, &outfd, left);
	ret = cmd_is_valid(exec);
	if (ret != 0)
	{
		free_exec(exec);
		exit (ret);
	}
	dup_fds(exec, infd, outfd, left);
	ret = is_builtin(exec);
	if (ret >= 0 && ret < 7)
		exit(exec_builtin(exec, ret));
	else
	{
		is_extern_cmd(exec, &cmd);
		exec_extern_cmd(exec, cmd);
	}
}

int exec_pipe(t_exec *exec)
{
	int	fd[2];
	int	pid[2];

	if (pipe(fd) == -1)
	{
		strerror(errno); //TODO to check again
		return (1);
	}
	pid[0] = fork();
	if (pid[0] == -1)
		return (handle_fork_error(fd, "fork"));
	if (pid[0] == 0)
		handle_pipe_process(exec, fd, true); //envoyer seulement si AST_CMD
}
