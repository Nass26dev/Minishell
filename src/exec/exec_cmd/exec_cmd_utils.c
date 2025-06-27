/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:03:03 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/27 14:32:26 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_fds(t_exec *exec)
{
	if (exec->infd > 2)
		close(exec->infd);
	if (exec->outfd > 2)
		close(exec->outfd);
	if (exec->heredoc)
		unlink_heredoc(exec->heredoc);
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
	if (!exec->current->command[0] || !exec->current->command[0][0])
	{
		close_fds(exec);
		printf("command not found\n");
		return (CMD_NOT_FOUND);
	}
	return (0);
}

int	return_process(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	handle_fork_error(int pipefd[2], int error, int pipe)
{
	int		len;
	char	*msg;

	if (error == EAGAIN)
		msg = "minishell: fork: Resource temporarily unavailable\n";
	else if (error == ENOMEM)
		msg = "minishell: fork: Not enough space\n";
	else if (error == ENOSPC)
		msg = "minishell: fork: No space left on device\n";
	else
		msg = "minishell: fork: Unknown error\n";
	len = ft_strlen(msg);
	if (len > 0)
		write(2, msg, len);
	if (pipe == 1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	return (FAIL_FORK);
}
