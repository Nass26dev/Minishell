/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:14:18 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/30 17:37:06 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*one_free_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	str = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	j = 0;
	while (s1[j])
		str[++i] = s1[j++];
	j = 0;
	while (s2[j])
		str[++i] = s2[j++];
	str[++i] = 0;
	free(s1);
	return (str);
}

bool	char_is_redir(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}
