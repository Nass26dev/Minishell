/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:03:03 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/12 12:04:46 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_fds(t_exec *exec)
{
	if (exec->infd != STDIN_FILENO)
		close(exec->infd);
	if (exec->outfd != STDOUT_FILENO)
		close(exec->outfd);
}

void	dup_fds(t_exec *exec)
{
	if (exec->infd != STDIN_FILENO)
		dup2(exec->infd, STDIN_FILENO);
	if (exec->outfd != STDOUT_FILENO)
		dup2(exec->outfd, STDOUT_FILENO);
	close_fds(exec);
}

int	cmd_is_valid(t_exec *exec)
{
	if (!exec || !exec->current)
		return (CMD_NOT_FOUND);
	if (!exec->current->cmd || !exec->current->cmd->data
		|| !exec->current->cmd->data[0] || !exec->current->cmd->data[0][0])
	{
		close_fds(exec);
		printf("command not found\n");
		return (CMD_NOT_FOUND);
	}
	return (0);
}

int	return_process(t_exec *exec)
{
	if (WIFEXITED(exec->shell->status))
		return (WEXITSTATUS(exec->shell->status));
	else if (WIFSIGNALED(exec->shell->status))
		return (128 + WTERMSIG(exec->shell->status));
	return (exec->shell->status);
}
