/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:01:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/15 18:47:23 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>

int	handle_redir_in(t_exec *exec)
{
	int	fd;

	fd = open(exec->current->command[0], O_RDONLY);
	if (fd == -1)
	{
		write_fd(exec->current->command[0], NULL, strerror(errno), 2);
		return (1);
	}
	if (exec->infd > 2)
		close(exec->infd);
	exec->infd = fd;
	return (0);
}

int	handle_redir_out(t_exec *exec)
{
	int	fd;

	fd = open(exec->current->command[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write_fd(exec->current->command[0], NULL, strerror(errno), 2);
		return (1);
	}
	if (exec->outfd > 2)
		close(exec->outfd);
	exec->outfd = fd;
	return (0);
}

int	handle_append(t_exec *exec)
{
	int	fd;

	fd = open(exec->current->command[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		write_fd(exec->current->command[0], NULL, strerror(errno), 2);
		return (1);
	}
	if (exec->outfd > 2)
		close(exec->outfd);
	exec->outfd = fd;
	return (0);
}

int	exec_redir(t_exec *exec)
{
	if (exec->current->tag == REDIR_IN)
		exec->shell->status = handle_redir_in(exec);
	else if (exec->current->tag == REDIR_OUT)
		exec->shell->status = handle_redir_out(exec);
	else if (exec->current->tag == APPEND)
		exec->shell->status = handle_append(exec);
	if (exec->shell->status != 0)
	{
		if (exec->infd > 2)
			close(exec->infd);
		if (exec->outfd > 2)
			close(exec->outfd);
		return (exec->shell->status);
	}
	exec->current = exec->current->left;
	return (exec_node(exec));
}
