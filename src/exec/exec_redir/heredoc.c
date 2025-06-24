/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:33 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/24 17:55:47 by eelissal         ###   ########lyon.fr   */
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
		free(tmp_path);
		perror("Failed to reopen heredoc file");
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
		perror("Failed to create random path for tmp file creation");
		return (1);
	}
	printf("Heredoc file: %s\n", tmp_path);
	fd = open(tmp_path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		printf("%s: %s\n", tmp_path, strerror(errno));
		return (1); //to check again
	}
	readline_heredoc(exec);
	if (reopen_fd_read(&fd, tmp_path) == false)
		return (1);
	unlink(tmp_path);
	free(tmp_path);
	if (exec->infd != STDIN_FILENO)
		close(exec->infd);
	exec->infd = fd;
	return (0);
}
