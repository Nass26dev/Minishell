/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:03:03 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/15 18:29:29 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_fds(t_exec *exec)
{
	if (exec->infd > 2)
		close(exec->infd);
	if (exec->outfd > 2)
		close(exec->outfd);
}

void	dup_fds(t_exec *exec, char *cmd)
{
	if (exec->infd != STDIN_FILENO)
	{
		if (dup2(exec->infd, STDIN_FILENO) == -1)
			handle_dup_error(exec, cmd, -1, -1);
	}
	if (exec->outfd != STDOUT_FILENO)
	{
		if (dup2(exec->outfd, STDOUT_FILENO) == -1)
			handle_dup_error(exec, cmd, -1, -1);
	}
	close_fds(exec);
}

int	cmd_is_valid(t_exec *exec)
{
	if (!exec || !exec->current)
		return (CMD_NOT_FOUND);
	if (!exec->current->command[0] || !exec->current->command[0][0])
	{
		close_fds(exec);
		write_fd(NULL, NULL, "command not found", 2);
		return (CMD_NOT_FOUND);
	}
	return (0);
}

int	return_process(int status, int last_pipe)
{
	int	signal;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGINT)
			write(2, "\n", 1);
		if (signal == SIGQUIT && last_pipe == 1)
			write(2, "Quit (core dumped)\n", 20);
		return (128 + signal);
	}
	return (status);
}
