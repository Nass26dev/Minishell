/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:37:22 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/14 16:16:41 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_dup_error(t_exec *exec, char *cmd, int infd, int outfd)
{
	write_fd("dup", NULL, strerror(errno), 2);
	free(cmd);
	if (infd > 2)
		close(infd);
	if (outfd > 2)
		close(outfd);
	close_fds(exec);
	free_exec(exec);
	exit (1);
}

int	handle_fork_error(t_exec *exec, int pipefd[2], int error, int pipe)
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
	exec->shell->status = FAIL_FORK + errno;
	return (exec->shell->status);
}

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->shell)
		free_shell(exec->shell);
	if (exec->root)
		free_ast(exec->root);
}

void	free_all(t_exec *exec)
{
	if (exec)
		free_exec(exec);
	rl_clear_history();
}
