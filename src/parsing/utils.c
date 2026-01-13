/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:08:54 by nass              #+#    #+#             */
/*   Updated: 2025/07/16 12:57:45 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_isspace(char c)
{
	if (c == ' ')
		return (true);
	else if (c == '\t')
		return (true);
	else if (c == '\n')
		return (true);
	else if (c == '\v')
		return (true);
	else if (c == '\f')
		return (true);
	else if (c == '\r')
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	if (c == '<')
		return (true);
	else if (c == '>')
		return (true);
	else if (c == '|')
		return (true);
	else if (c == '&')
		return (true);
	return (false);
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	while (i < n && src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

bool	true_exit(t_tag tag, t_data *data)
{
	print_correct_error(tag, data);
	return (true);
}

int	event_hook(void)
{
	return (1);
}
