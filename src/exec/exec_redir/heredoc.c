/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:33 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/27 16:25:35 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>

void	readline_heredoc(t_exec *exec, int fd)
{
	char	*delimiter;
	char	*line;
	int		len;

	delimiter = exec->current->command[0];
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		len = strlen(line);
		write(fd, line, len);
		write(fd, "\n", 1);
		free(line);
	}
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

static char	*add_num(int i)
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

static char	*create_file(void)
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

int	create_heredoc(t_exec **exec, char **tmp_path, int *fd)
{
	*tmp_path = create_file();
	if (!*tmp_path)
	{
		write_fd(*tmp_path, NULL, "Failed to create random path in heredoc", 2);
		return (1);
	}
	*fd = open(*tmp_path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (*fd == -1)
	{
		write_fd(*tmp_path, NULL, strerror(errno), 2);
		return (1);
	}
	if (!(*exec)->heredoc)
		(*exec)->heredoc = vector_create(1);
	if (!(*exec)->heredoc || vector_add((*exec)->heredoc, *tmp_path) == false)
	{
		close(*fd);
		free(*tmp_path);
		return (1);
	}
	return (0);
}
