#include "exec.h"
#include <fcntl.h>

static char	*copy_path(int bytes_read, unsigned char *random_bytes)
{
	char	*tmp_path;
	int		i;
	int		j;

	tmp_path = malloc(sizeof(char) * 16);
	if (!tmp_path)
		return (NULL);
	ft_memcpy(tmp_path, "/tmp/", 5);
	tmp_path[5] = '\0';
	i = 5;
	j = 0;
	while (j < bytes_read && i < 15)
	{
		if (ft_isalnum(random_bytes[j]) == 1)
		{
			tmp_path[i] = random_bytes[j];
			i++;
		}
		j++;
	}
	tmp_path[i] = '\0';
	return (tmp_path);
}

static char	*get_random_path(void)
{
	unsigned char	random_bytes[100];
	char			*tmp_path;
	int				fd;
	int				bytes_read;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	bytes_read = read(fd, random_bytes, 100);
	close(fd);
	if (bytes_read <= 0)
		return (NULL);
	tmp_path = copy_path(bytes_read, random_bytes);
	if (!tmp_path)
		return (NULL);
	return (tmp_path);
}

static void	readline_heredoc(t_exec *exec, int *fd)
{
	char	*delimiter;
	char	*line;

	delimiter = exec->current->cmd->data[0];
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
        (void) fd;
        // heredoc expansion
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

/*Creates random path with prefix \tmp\, then open tmp file.
Gets delimiter from AST node. Reads heredoc content line
by line and write content to tmp file.
Closes file that was in writing to reopen it in reading.
Deletes file but keeps fd open and set infd and exec cmd*/
int	handle_heredoc(t_exec *exec)
{
	char	*tmp_path;
	int		fd;

	tmp_path = get_random_path();
	if (!tmp_path)
	{
		perror("Failed to create random path for tmp file creation");
		return (1);
	}
	fd = open(tmp_path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		printf("%s: %s\n", tmp_path, strerror(errno));
		return (1); //to check again
	}
	readline_heredoc(exec, &fd);
	if (reopen_fd_read(&fd, tmp_path) == false)
		return (1);
	unlink(tmp_path);
	free(tmp_path);
	if (exec->infd != STDIN_FILENO)
		close(exec->infd);
	exec->infd = fd;
	exec->current = exec->current->left;
	return (exec_node(exec));
}
