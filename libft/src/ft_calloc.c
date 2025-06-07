/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:49:36 by eelissal          #+#    #+#             */
/*   Updated: 2024/11/29 19:28:13 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size > SIZE_MAX / nmemb)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}
/*
int	main(void)
{
	size_t	nmemb = 10;
	size_t	size = 4;
	size_t	i = 0;
	char	*ptr;

	ptr = ft_calloc(nmemb, size);
	while (i < size * nmemb)
	{
		if (ptr[i] != '\0')
			return (1);
		i++;
	}
	free(ptr);
	return (0);
}*/