/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:16:17 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/26 17:40:10 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	parse_trailing_newline(const char *str, char n)
{
	int	i;

	if (!str || str[0] != '-')
		return (-1);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != n)
			return (-1);
		i++;
	}
	return (0);
}

int	builtin_echo(char **data, int fd)
{
	int		i;
	bool	n_flag;
	int		len;

	i = 1;
	n_flag = true;
	while (data[i] && parse_trailing_newline(data[i], 'n') == 0)
	{
		n_flag = false;
		i++;
	}
	while (data[i])
	{
		len = ft_strlen(data[i]);
		if (len > 0)
		{
			write(fd, data[i], len);
			if (data[i + 1])
				write(fd, " ", 1);
		}
		i++;
	}
	if (n_flag == true)
		write(fd, "\n", 1);
	return (0);
}
