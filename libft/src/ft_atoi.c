/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:56:06 by eelissal          #+#    #+#             */
/*   Updated: 2024/11/25 16:46:40 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] && (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (sign == -1 && (LONG_MIN / 10 > -res
				|| 10 * -res < LONG_MIN + (nptr[i] - 48)))
			return (0);
		if (sign == 1 && (LONG_MAX / 10 < res
				|| res * 10 > LONG_MAX - (nptr[i] - 48)))
			return (-1);
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}
