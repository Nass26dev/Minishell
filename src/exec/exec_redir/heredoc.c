/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:33 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/04 15:24:59 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>

int	event_hook(void)
{
	return (1);
}

int	readline_heredoc(t_exec *exec, int fd, char *tmp_path)
{
	char	*delimiter;
	char	*line;
	int		len;

	(void)tmp_path;
	delimiter = exec->current->command[0];
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		if (g_received_signal == SIGINT)
		{
			g_received_signal = 0;
			exec->shell->status = 130;
			break ;
		}
		len = ft_strlen(line);
		write(fd, line, len);
		write(fd, "\n", 1);
		free(line);
	}
	return (exec->shell->status);
}

bool	reopen_fd_read(int *fd, char *tmp_path)
{
	close(*fd);
	*fd = open(tmp_path, O_RDONLY);
	if (*fd == -1)
	{
		write_fd(tmp_path, NULL, "failed to reopen heredoc file", 2);
		free(tmp_path);
		return (false);
	}
	return (true);
}

void	unlink_one_heredoc(t_exec *exec)
{
	unlink(exec->heredoc->data[exec->heredoc->count - 1]);
	free(exec->heredoc->data[exec->heredoc->count - 1]);
	exec->heredoc->count--;
	if (exec->heredoc->count == 0)
	{
		free(exec->heredoc->data);
		free(exec->heredoc);
		exec->heredoc = NULL;
	}
}

void	set_new_infd(t_exec *exec, int fd)
{
	if (exec->infd > 2)
		close(exec->infd);
	if (exec->current->left)
		exec->infd = fd;
	else
	{
		close(fd);
		exec->infd = STDIN_FILENO;
	}
}
