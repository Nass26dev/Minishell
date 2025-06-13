/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:16:17 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/13 15:27:37 by eelissal         ###   ########lyon.fr   */
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

int	exec_echo(char **data)
{
	int		i;
	bool	n_flag;

	if (!data|| !data[0])
		return (EXIT_FAILURE);
	i = 1;
	n_flag = true;
	while (data[i] && parse_trailing_newline(data[i], 'n') == 0)
	{
		n_flag = false;
		i++;
	}
	while (data[i])
	{
		printf("%s", data[i]);
		if (data[i + 1])
			printf(" ");
		i++;
	}
	if (n_flag == true)
		printf("\n");
	return (EXIT_SUCCESS);
}
