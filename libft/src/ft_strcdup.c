/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:36:25 by eelissal          #+#    #+#             */
/*   Updated: 2025/03/23 22:36:43 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *s, char n)
{
	int		i;
	char	*dest;

	if (!s)
		return (NULL);
	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dest)
		return (0);
	while (s[i] && s[i] != n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
