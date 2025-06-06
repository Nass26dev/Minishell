/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:43:46 by eelissal          #+#    #+#             */
/*   Updated: 2024/11/23 18:58:31 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*src1;
	unsigned char	*src2;
	size_t			i;

	if (n == 0)
		return (0);
	src1 = (unsigned char *) s1;
	src2 = (unsigned char *) s2;
	i = 0;
	while ((src1[i] == src2[i]) && i + 1 < n)
		i++;
	return (src1[i] - src2[i]);
}
