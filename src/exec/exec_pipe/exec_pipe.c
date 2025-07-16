/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:08:50 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/16 12:38:30 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

static int	pipe_waitpid_process(pid_t pid[2], int last_pipe)
{
	int	ret;
	int	status1;
	int	status2;

	ret = -1;
	setup_waitpid_signals();
	waitpid(pid[0], &status1, 0);
	waitpid(pid[1], &status2, 0);
	ret = return_process(status2, last_pipe);
	if (ret == 0 && WTERMSIG(status1) == SIGINT)
		ret = return_process(status1, last_pipe);
	setup_interactive_signals();
	return (ret);
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
	{
		ret = exec_builtin(exec, ret);
		close_fds(exec);
		free_exec(exec);
		exit(ret);
	}
	else
	{
		is_extern_cmd(exec, &cmd);
		exec_extern_cmd(exec, cmd);
	}
}

static void	handle_pipe_child_process(t_exec *exec, int pipefd[2], int fd)
{
	int	status;

	setup_child_signals();
	while (exec->current && (is_redirection(exec->current->tag)))
	{
		exec = exec_redir_pipe(exec);
		if (exec->current == NULL)
			close_pipes(exec, pipefd, 1);
	}
	if (exec->current)
		handle_redirections(exec, pipefd, fd);
	if (exec-> current && exec->current->tag == CMD)
		handle_pipe_process(exec);
	else if (exec-> current && exec->current->tag == PIPE && fd == 0)
		exec->shell->status = exec_pipe(exec, 0);
	status = exec->shell->status;
	free_all_heredocs(&exec->heredoc);
	free_exec(exec);
	exit(status);
}

static int	exec_pipe_fork(t_exec *exec, int pipefd[2], pid_t pid[2], int fd)
{
	pid[fd] = fork();
	if (pid[fd] == -1)
	{
		if (fd == 1 && pid[0] > 0)
			waitpid(pid[0], NULL, 0);
		return (handle_fork_error(exec, pipefd, errno, 1));
	}
	if (pid[fd] == 0)
		handle_pipe_child_process(exec, pipefd, fd);
	return (0);
}

int	exec_pipe(t_exec *exec, int last_pipe)
{
	int		pipefd[2];
	pid_t	pid[2];
	t_ast	*current;

	if (pipe(pipefd) == -1)
	{
		write_fd("pipe", NULL, strerror(errno), 2);
		return (1);
	}
	current = exec->current;
	exec->current = exec->current->left;
	if (exec_pipe_fork(exec, pipefd, pid, 0) != 0)
		return (exec->shell->status);
	exec->current = current;
	close_pipes(exec, pipefd, 0);
	exec->current = exec->current->right;
	if (exec_pipe_fork(exec, pipefd, pid, 1) != 0)
		return (exec->shell->status);
	exec->current = current;
	close_pipes(exec, pipefd, 1);
	exec->shell->status = pipe_waitpid_process(pid, last_pipe);
	return (exec->shell->status);
}
