/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:08:54 by nass              #+#    #+#             */
/*   Updated: 2025/06/07 01:20:57 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool ft_isspace(char c)
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

bool is_operator(char c)
{
	if (c == '<')
		return (true);
	else if (c == '>')
		return (true);
	else if (c == '|')
		return (true);
	else if (c == '&')
		return (true);
	else if (c == '(')
		return (true);
	return (false);
}

char *ft_strndup(const char *src, size_t n)
{
    size_t i;
    char *dup;
    
    i = 0;
    dup = malloc(n + 1);
    if (!dup)
        return NULL;
    while (i < n && src[i])
    {
        dup[i] = src[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

int ft_isalnum(int c)
{
    if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	i = -1;
	str = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2)) + 1);
	if (!str)
		return (NULL);
	while (*s1)
		str[++i] = *s1++;
	while (*s2)
		str[++i] = *s2++;
	str[++i] = 0;
	return (str);
}
