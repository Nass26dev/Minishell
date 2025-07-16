/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:21:24 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/16 09:22:37 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
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
