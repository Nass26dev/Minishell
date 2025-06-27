/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:33 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:13 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>

static void	readline_heredoc(t_exec *exec)
{
	char	*delimiter;
	char	*line;

	delimiter = exec->current->command[0];
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

static bool	reopen_fd_read(int *fd, char *tmp_path)
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

char	*add_num(int i)
{
	char	*temp;
	char	*filename;

	temp = ft_itoa(i);
	if (!temp)
		return (NULL);
	filename = ft_strjoin(BASE_FILENAME, temp);
	free(temp);
	return (filename);
}

char	*create_file(void)
{
	int		fd;
	char	*filename;
	int		i;

	i = 1;
	while (i <= MAX_TRIES)
	{
		if (i == 1)
			filename = ft_strdup(BASE_FILENAME);
		else
			filename = add_num(i);
		if (!filename)
			return (NULL);
		fd = open(filename, O_CREAT | O_EXCL, 0777);
		if (fd != -1)
		{
			close(fd);
			return (filename);
		}
		i++;
		free(filename);
	}
	return (NULL);
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

	tmp_path = create_file();
	if (!tmp_path)
	{
		write_fd(tmp_path, NULL, "Failed to create random path for tmp file creation", 2);
		return (1);
	}
	fd = open(tmp_path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		write_fd(tmp_path, NULL, strerror(errno), 2);
		return (1);
	}
	if (!exec->heredoc)
		exec->heredoc = vector_create(1);
	if (!exec->heredoc || vector_add(exec->heredoc, tmp_path) == false)
	{
		close(fd);
		free(tmp_path);
		return (1);
	}
	setup_child_signals();
	readline_heredoc(exec);
	setup_interactive_signals();
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
