/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:01:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/04 12:40:04 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>

static int	event_hook(void)
{
	return (1);
}

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

/*Creates random path with prefix \tmp\, then open tmp file.
Gets delimiter from AST node. Reads heredoc content line
by line and write content to tmp file.
Closes file that was in writing to reopen it in reading.
Deletes file but keeps fd open and set infd and exec cmd*/
int	handle_heredoc(t_exec *exec)
{
	char	*tmp_path;
	int		fd;
	int		ret;

	tmp_path = NULL;
	if (create_heredoc(&exec, &tmp_path, &fd) == 1)
		return (1);
	setup_heredoc_signals();
	rl_event_hook = event_hook;
	ret = readline_heredoc(exec, fd, tmp_path) != 0;
	rl_event_hook = NULL;
	setup_interactive_signals();
	if (ret != 0)
			return (exec->shell->status);
	if (reopen_fd_read(&fd, tmp_path) == false)
		return (1);
	unlink(exec->heredoc->data[exec->heredoc->count - 1]);
	free(exec->heredoc->data[exec->heredoc->count - 1]);
	free(tmp_path);
	exec->heredoc->count--;
	if (exec->heredoc->count == 0)
	{
		free(exec->heredoc->data);
		free(exec->heredoc);
		exec->heredoc = NULL;
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
	else if (exec->current->tag == HEREDOC)
		exec->shell->status = handle_heredoc(exec);
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
