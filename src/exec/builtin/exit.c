/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:59:00 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/27 16:38:05 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_overflow(int n)
{
	if (n < 0 || n > 255)
	{
		while (n < 0)
			n = n + 256;
		n = n % 256;
	}
	return (n);
}

int	arg_is_digit(t_exec *exec)
{
	char	*data;
	int		j;

	data = exec->current->command[1];
	j = 0;
	if (data[0] == '+' || data[0] == '-')
		j++;
	while (data[j])
	{
		if (ft_isdigit(data[j]) == 0)
		{
			printf("exit\n");
			write_fd("exit", data, "numeric argument required", 2);
			exec->shell->status = 2;
			return (1);
		}
		j++;
	}
	return (0);
}

static bool	exit_with_args(t_exec *exec, int i, int status)
{
	int	result;

	if (i >= 2)
	{
		if (arg_is_digit(exec) != 0)
		{
			free_all(exec);
			exit(2);
		}
		if (i > 2)
		{
			printf("exit\n");
			write_fd("exit", NULL, "too many arguments", 2);
			return (false);
		}
		else
		{
			result = ft_atoi(exec->current->command[1]);
			status = check_overflow(result);
			free_all(exec);
			printf("exit\n");
			exit (status);
		}
	}
	return (true);
}

int	builtin_exit(t_exec *exec)
{
	int	i;
	int	status;

	i = 0;
	status = exec->shell->status;
	while (exec->current->command[i])
		i++;
	if (i == 1)
	{
		printf("exit\n");
		free_all(exec);
		exit(status);
	}
	if (exit_with_args(exec, i, status) != false)
		return (1);
	return (1);
}
