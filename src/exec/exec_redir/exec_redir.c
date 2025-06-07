/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:01:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/07 20:44:17 by codespace        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>

static int	handle_redir_in(t_exec *exec)
{
	int	fd;

	fd = open(exec->current->cmd->data[0], O_RDONLY);
	if (fd == -1)
	{
		printf("%s: %s\n", exec->current->cmd->data[0], strerror(errno));
		return (1); //to check again
	}
	if (exec->infd != STDIN_FILENO)
		close(exec->infd);
	exec->infd = fd;
	exec->current = exec->current->left;
	return (exec_node(exec));
}

static int	handle_redir_out(t_exec *exec)
{
	int	fd;

	fd = open(exec->current->cmd->data[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("%s: %s\n", exec->current->cmd->data[0], strerror(errno));
		return (1); //to check again
	}
	if (exec->outfd != STDOUT_FILENO)
		close(exec->outfd);
	exec->outfd = fd;
	exec->current = exec->current->left;
	return (exec_node(exec));
}

static int	handle_append(t_exec *exec)
{
	int	fd;

	fd = open(exec->current->cmd->data[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("%s: %s\n", exec->current->cmd->data[0], strerror(errno));
		return (128 + errno); //to check again
	}
	if (exec->outfd != STDOUT_FILENO)
		close(exec->outfd);
	exec->outfd = fd;
	exec->current = exec->current->left;
	return (exec_node(exec));
}

int	exec_redir(t_exec *exec)
{
	if (exec->current->tag == AST_REDIR_IN)
		return (handle_redir_in(exec));
	else if (exec->current->tag == AST_HEREDOC)
		return (handle_heredoc(exec));
	else if (exec->current->tag == AST_REDIR_OUT)
		return (handle_redir_out(exec));
	else if (exec->current->tag == AST_APPEND)
		return (handle_append(exec));
	return (0);
}
