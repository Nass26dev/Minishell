/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:34:26 by eelissal          #+#    #+#             */
/*   Updated: 2024/12/09 15:39:26 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_strlen_bonus(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strchr_bonus(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char) s[i] == (unsigned char) c)
			return ((char *) s + i);
		i++;
	}
	if ((unsigned char) s[i] == (unsigned char) c)
		return ((char *) s + i);
	return (NULL);
}

int	ft_putchar_bonus(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_bonus(char *s)
{
	int	count;

	count = 0;
	if (!s)
		count += write(1, "(null)", 6);
	while (s && *s)
	{
		count += ft_putchar_bonus(*s);
		s++;
	}
	return (count);
}

int	ft_unsigned_bonus(unsigned int n)
{
	unsigned int	nbr;
	unsigned long	ten_power;
	int				count;

	ten_power = 1;
	nbr = n;
	count = 0;
	while (nbr / (ten_power * 10) != 0)
		ten_power *= 10;
	while (ten_power != 0)
	{
		count += ft_putchar_bonus((nbr / ten_power) + '0');
		nbr = nbr % ten_power;
		ten_power = ten_power / 10;
	}
	return (count);
}
