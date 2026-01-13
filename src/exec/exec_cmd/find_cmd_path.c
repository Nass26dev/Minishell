/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:57:11 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/27 16:45:08 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_directory(const char *path)
{
	struct stat	buffer;

	if (stat(path, &buffer) != 0)
		return (0);
	return (S_ISDIR(buffer.st_mode));
}

static char	*find_executable_path(char *cmd, char **path_dirs)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		cmd_path = malloc(sizeof(char) * ft_strlen(path_dirs[i])
				+ ft_strlen(cmd) + 2);
		if (!cmd_path)
		{
			free_args(path_dirs);
			return (NULL);
		}
		ft_strlcpy(cmd_path, path_dirs[(i)], ft_strlen(path_dirs[(i)]) + 1);
		ft_strlcat(cmd_path, "/", ft_strlen(cmd_path) + 2);
		ft_strlcat(cmd_path, cmd, ft_strlen(cmd_path) + ft_strlen(cmd) + 1);
		if (access(cmd_path, F_OK | X_OK) != 0)
		{
			free(cmd_path);
			i++;
		}
		else
			return (cmd_path);
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd_name, t_vector *env)
{
	char	*cmd_path;
	char	*path;
	char	**path_dirs;

	if (ft_strchr(cmd_name, '/'))
	{
		if (access(cmd_name, F_OK | X_OK) != 0)
			return (strerror(errno), NULL);
		return (ft_strdup(cmd_name));
	}
	else
	{
		path = get_env(env, "PATH");
		if (!path)
			return (NULL);
		path_dirs = ft_split(path, ':');
		free(path);
		if (!path_dirs)
			return (NULL);
		cmd_path = find_executable_path(cmd_name, path_dirs);
		free_args(path_dirs);
	}
	return (cmd_path);
}
