/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 16:07:31 by eelissal          #+#    #+#             */
/*   Updated: 2024/12/09 15:54:45 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_width(char conversion, t_flags *flags, va_list tmp_args)
{
	if (conversion == 'c')
		flags->width -= 1;
	else if (conversion == 's')
		flags->width -= ft_strlen_bonus(va_arg(tmp_args, char *));
	else if (conversion == 'p')
		flags->width -= 2 + ft_hexlen((long long)va_arg(tmp_args, void *));
	else if (conversion == 'u')
		flags->width -= ft_nbrlen((long long)va_arg(tmp_args, unsigned int));
	else if (conversion == 'x' || conversion == 'X')
		flags->width -= ft_hexlen((long long)va_arg(tmp_args, unsigned int));
	else if (conversion == 'd' || conversion == 'i')
		flags->width -= ft_nbrlen((long long)va_arg(tmp_args, int));
	if (flags->width < 0)
		flags->width = 0;
	va_end(tmp_args);
}

int	ft_left_padding(t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->right_padding == false)
	{
		while (count < flags->width)
			count += ft_putchar_bonus(flags->pad_char);
	}
	return (count);
}

int	ft_right_padding(t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->right_padding == true)
	{
		flags->pad_char = ' ';
		while (count < flags->width)
			count += ft_putchar_bonus(flags->pad_char);
	}
	return (count);
}

int	ft_nbrlen(long long nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr = -nbr;
		len++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

int	ft_hexlen(long long nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr /= 16;
		len++;
	}
	return (len);
}
