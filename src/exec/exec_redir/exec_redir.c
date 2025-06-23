/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:01:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/20 22:50:06 by nass             ###   ########.fr       */
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
		printf("%s: %s\n", exec->current->command[0], strerror(errno));
		return (1); //TODO to check again
	}
	if (exec->infd != STDIN_FILENO)
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
		printf("%s: %s\n", exec->current->command[0], strerror(errno));
		return (1); //TODO to check again
	}
	if (exec->outfd != STDOUT_FILENO)
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
		printf("%s: %s\n", exec->current->command[0], strerror(errno));
		return (128 + errno); //TODO to check again
	}
	if (exec->outfd != STDOUT_FILENO)
		close(exec->outfd);
	exec->outfd = fd;
	return (0);
}

int	exec_redir(t_exec *exec)
{
	int	ret;

	(void)ret;
	if (exec->current->tag == TOKEN_REDIR_IN)
		ret = handle_redir_in(exec);
	else if (exec->current->tag == TOKEN_HEREDOC)
		ret = handle_heredoc(exec);
	else if (exec->current->tag == TOKEN_REDIR_OUT)
		ret = handle_redir_out(exec);
	else if (exec->current->tag == TOKEN_APPEND)
		ret = handle_append(exec);
	exec->current = exec->current->left;
	return (exec_node(exec));
}
