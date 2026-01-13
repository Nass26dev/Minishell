/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:20:59 by eelissal          #+#    #+#             */
/*   Updated: 2024/12/09 18:00:21 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_conversion_bonus(char conversion, t_flags *flags, va_list args)
{
	int	count;

	count = 0;
	count += ft_left_padding(flags);
	if (conversion == 'c')
		count += ft_putchar_bonus(va_arg(args, int));
	else if (conversion == 's')
		count += ft_putstr_bonus(va_arg(args, char *));
	else if (conversion == 'p')
		count += ft_ptrhexa_bonus(va_arg(args, void *));
	else if (conversion == 'u')
		count += ft_unsigned_bonus(va_arg(args, unsigned int));
	else if (conversion == 'x')
		count += ft_puthexa_low_bonus(va_arg(args, unsigned int), flags);
	else if (conversion == 'X')
		count += ft_puthexa_up_bonus(va_arg(args, unsigned int), flags);
	else if (conversion == 'd' || conversion == 'i')
		count += ft_putnbr_bonus(va_arg(args, int), flags, 1, 0);
	count += ft_right_padding(flags);
	return (count);
}

static void	ft_reset_flags(t_flags *flags)
{
	flags->hashtag = false;
	flags->space = false;
	flags->plus = false;
	flags->right_padding = false;
	flags->width = 0;
	flags->pad_char = ' ';
}

static void	ft_parse_flags(const char **format, t_flags *flags)
{
	ft_reset_flags(flags);
	while (**format && ft_strchr_bonus("# +-0", **format))
	{
		if (**format == '#')
			flags->hashtag = true;
		if (**format == ' ')
			flags->space = true;
		if (**format == '+')
			flags->plus = true;
		if (**format == '-')
			flags->right_padding = true;
		if (**format == '0')
			flags->pad_char = '0';
		(*format)++;
	}
	while (**format >= '0' && **format <= '9')
	{
		flags->width = flags->width * 10 + (**format - 48);
		(*format)++;
	}
}

static int	ft_parsing_bonus(const char *format, va_list args)
{
	int		total_char;
	t_flags	flags;
	va_list	tmp_args;

	total_char = 0;
	while (*format)
	{
		if (*format == '%' && (*format + 1))
		{
			format++;
			ft_parse_flags(&format, &flags);
			if ((ft_strchr_bonus("cspdiuxX", *format)))
			{
				va_copy(tmp_args, args);
				ft_width(*format, &flags, tmp_args);
				total_char += ft_conversion_bonus(*format, &flags, args);
			}
			else if (*format == '%')
				total_char += ft_putchar_bonus('%');
		}
		else
			total_char += ft_putchar_bonus(*format);
		format++;
	}
	return (total_char);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total_char;

	if (!format)
		return (-1);
	va_start(args, format);
	total_char = ft_parsing_bonus(format, args);
	va_end(args);
	return (total_char);
}
