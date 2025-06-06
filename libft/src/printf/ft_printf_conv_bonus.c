/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:23:47 by eelissal          #+#    #+#             */
/*   Updated: 2024/12/09 15:39:02 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_putnbr_bonus(int n, t_flags *flags, long ten_power, int count)
{
	long	nbr;

	nbr = n;
	if (n >= 0)
	{
		if (flags->plus)
			count += ft_putchar_bonus('+');
		else if (flags->space && !flags->plus)
			count += ft_putchar_bonus(' ');
	}
	if (nbr < 0)
	{
		nbr = nbr * -1;
		count += ft_putchar_bonus('-');
	}
	while (nbr / (ten_power * 10) != 0)
		ten_power *= 10;
	while (ten_power != 0)
	{
		count += ft_putchar_bonus((nbr / ten_power) + 48);
		nbr %= ten_power;
		ten_power /= 10;
	}
	return (count);
}

int	ft_putnbr_base_bonus(unsigned long nbr, char *base)
{
	unsigned long	len_base;
	int				count;

	len_base = ft_strlen_bonus(base);
	count = 0;
	if (nbr >= len_base)
	{
		count += ft_putnbr_base_bonus(nbr / len_base, base);
		count += ft_putchar_bonus(base[nbr % len_base]);
	}
	else
		count += ft_putchar_bonus(base[nbr % len_base]);
	return (count);
}

int	ft_puthexa_low_bonus(unsigned long n, t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->hashtag == true && n != 0)
		count += ft_putstr_bonus("0x");
	count += ft_putnbr_base_bonus(n, "0123456789abcdef");
	return (count);
}

int	ft_puthexa_up_bonus(unsigned long n, t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->hashtag == true && n != 0)
		count += ft_putstr_bonus("0X");
	count += ft_putnbr_base_bonus(n, "0123456789ABCDEF");
	return (count);
}

int	ft_ptrhexa_bonus(void *ptr)
{
	int				count;
	unsigned long	address;

	count = 0;
	if (!ptr)
		count += ft_putstr_bonus("(nil)");
	else
	{
		address = (unsigned long) ptr;
		count += ft_putstr_bonus("0x");
		count += ft_putnbr_base_bonus(address, "0123456789abcdef");
	}
	return (count);
}
