/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:42:30 by eelissal          #+#    #+#             */
/*   Updated: 2025/03/06 15:13:07 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	strlen_gnl(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

void	*ft_memset_gnl(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	ch;
	unsigned char	*dest;

	i = 0;
	dest = (unsigned char *)s;
	ch = (unsigned char)c;
	while (i < n)
	{
		dest[i] = ch;
		i++;
	}
	return (s);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char) s[i] == (unsigned char) c)
			return ((char *) s + i);
		i++;
	}
	if ((unsigned char) s[i] == (unsigned char) c)
		return ((char *) s + i);
	return (0);
}

char	*ft_strjoin_gnl(char *line, char *buffer)
{
	char	*dest;
	int		i;
	int		j;

	if (!line || !buffer)
		return (NULL);
	dest = malloc(sizeof(char) * (strlen_gnl(line) + strlen_gnl(buffer)) + 1);
	if (!dest)
	{
		free(line);
		return (NULL);
	}
	i = -1;
	while (++i < strlen_gnl(line))
		dest[i] = line[i];
	j = 0;
	while (j < strlen_gnl(buffer))
	{
		dest[i + j] = buffer[j];
		j++;
	}
	dest[i + j] = '\0';
	free(line);
	return (dest);
}

char	*ft_strdup_gnl(char *s)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (strlen_gnl(s) + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
