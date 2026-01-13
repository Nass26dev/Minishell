/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:26:38 by eelissal          #+#    #+#             */
/*   Updated: 2024/11/25 16:30:04 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_sep(char const *str, char sep)
{
	if (str[0] == sep)
		return (1);
	return (0);
}

static int	ft_count_words(char const *str, char sep)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (!ft_is_sep(&str[i], sep))
		{
			count++;
			while (str[i] && !ft_is_sep(&str[i], sep))
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	ft_size_next_word(char const *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && !ft_is_sep(&str[i], sep))
	{
		i++;
	}
	return (i);
}

static int	alloc_cpy_next_word(char const *str, char **array, char sep, int y)
{
	int	x;

	x = 0;
	array[y] = malloc(sizeof(char) * (ft_size_next_word(str, sep) + 1));
	if (!array[y])
	{
		while (y)
			free(array[--y]);
		free(array);
		return (-1);
	}
	while (str[x] && !ft_is_sep(&str[x], sep))
	{
		array[y][x] = str[x];
		x++;
	}
	array[y][x] = 0;
	return (x);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		size;
	int		y;
	int		res;

	y = 0;
	size = ft_count_words(s, c);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (0);
	while (y < size)
	{
		while (s[0] && ft_is_sep(s, c))
			s += ft_is_sep(s, c);
		res = alloc_cpy_next_word(s, array, c, y);
		if (res == -1)
			return (NULL);
		s += res;
		y++;
	}
	array[y] = NULL;
	return (array);
}
