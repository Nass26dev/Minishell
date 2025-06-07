/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:41:48 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/07 20:30:10 by codespace        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = 0;
	while ((c1[i] != '\0' || c2[i] != '\0'))
	{
		if (c1[i] > c2[i])
			return (1);
		if (c1[i] < c2[i])
			return (-1);
		i++;
	}
	if (c1[i] > c2[i])
		return (1);
	if (c1[i] < c2[i])
		return (-1);
	return (0);
}
