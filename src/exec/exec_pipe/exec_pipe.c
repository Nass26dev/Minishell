/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:08:50 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/09 18:50:03 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

static int	waitpid_process(t_exec *exec, int pid[2])
{
	waitpid(pid[0], &exec->shell->status, 0);
	if (pid[0] > 0)
		waitpid(pid[1], &exec->shell->status, 0);
	if (WIFEXITED(exec->shell->status))
		return (WEXITSTATUS(exec->shell->status));
	else if (WIFSIGNALED(exec->shell->status))
		return (128 + WTERMSIG(exec->shell->status));
	return (exec->shell->status);
}

static void	dup_infds(t_exec *exec, int pipefd[2])
{
	close(pipefd[1]);
	if (exec->infd != STDIN_FILENO)
	{
		dup2(exec->infd, STDIN_FILENO);
		close(exec->infd);
	}
	else
		dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

static void	dup_outfds(t_exec *exec, int pipefd[2])
{
	close(pipefd[0]);
	if (exec->outfd != STDOUT_FILENO)
	{
		dup2(exec->outfd, STDOUT_FILENO);
		close(exec->outfd);
	}
	else
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
}

static void	handle_pipe_process(t_exec *exec, int pipefd[2], bool left)
{
	char	cmd;
	int		ret;

	ret = cmd_is_valid(exec);
	if (ret != 0)
		exit (ret);
	if (left == true)
	{
		dup_outfds(exec, pipefd);
		exec->current = exec->current->left;
	}
	else
	{
		dup_infds(exec, pipefd);
		exec->current = exec->current->right;
	}
	ret = is_builtin(exec);
	if (ret >= 0 && ret < 7)
		exit(exec_builtin(exec, ret));
	else
	{
		is_extern_cmd(exec, &cmd);
		exec_extern_cmd(exec, &cmd);
	}
}

static int	handle_fork_error(int pipefd[2], const char *msg)
{
	perror(msg);
	close(pipefd[0]);
	close(pipefd[1]);
	return (FAIL_FORK);
}

int	exec_pipe(t_exec *exec)
{
	int	infd;
	int	outfd;
	int	pipefd[2];
	int	pid[2];
	
	infd = exec->infd;
	outfd = exec->outfd;
	// TODO printf("infd: %d\noutfd: %d\n", infd, outfd);
	if (pipe(pipefd) == -1)
	{
		strerror(errno); //TODO to check again
		return (1);
	}
	pid[0] = fork();
	if (pid[0] == -1)
		return (handle_fork_error(pipefd, "fork"));
	if (pid[0] == 0)
		handle_pipe_process(exec, pipefd, true);
	pid[1] = fork();
	if (pid[1] == -1)
		return (handle_fork_error(pipefd, "fork"));
	if (pid[1] == 0)
		handle_pipe_process(exec, pipefd, false);
	close(pipefd[0]);
	close(pipefd[1]);
	exec->infd = infd;
	exec->outfd = outfd;
	return (waitpid_process(exec, pid));
}
