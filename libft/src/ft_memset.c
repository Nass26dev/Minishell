/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:32:17 by eelissal          #+#    #+#             */
/*   Updated: 2024/11/23 18:58:49 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
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
