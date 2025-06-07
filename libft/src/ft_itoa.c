/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:11:14 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/07 01:48:02 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int				count;
	unsigned int	nb;

	count = 1;
	if (n < 0)
	{
		count++;
		nb = n * -1;
	}
	else
		nb = n;
	while (nb > 9)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static char	*ft_cpy_array(char *array, int n, int len)
{
	int				i;
	unsigned int	nb;

	if (n == 0)
		array[0] = '0';
	if (n < 0)
	{
		array[0] = '-';
		nb = n * -1;
	}
	else
		nb = n;
	i = len - 1;
	while (nb > 0)
	{
		array[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	array[len] = '\0';
	return (array);
}

char	*ft_itoa(int n)
{
	char	*array;
	int		len;

	len = ft_count_digits(n);
	array = malloc(sizeof(char) * len + 1);
	if (!array)
		return (NULL);
	array = ft_cpy_array(array, n, len);
	return (array);
}
