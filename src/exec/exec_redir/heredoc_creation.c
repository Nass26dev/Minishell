/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:21:24 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/04 15:23:36 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>

static char	*add_num(int i)
{
	char	*temp;
	char	*filename;

	temp = ft_itoa(i);
	if (!temp)
		return (NULL);
	filename = ft_strjoin(BASE_FILENAME, temp);
	if (!filename)
	{
		free(temp);
		return (NULL);
	}
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
