/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:26:31 by eelissal          #+#    #+#             */
/*   Updated: 2024/11/23 19:00:07 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_s;
	size_t	len_d;
	size_t	i;
	size_t	j;

	i = 0;
	len_s = ft_strlen(src);
	len_d = ft_strlen (dst);
	j = 0;
	while (dst[j])
		j++;
	if (size <= len_d)
		return (len_s + size);
	while (src[i] && (i < size - len_d - 1))
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (len_s + len_d);
}
