/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:59:00 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/20 10:23:01 by eelissal         ###   ########lyon.fr   */
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
			printf("minishell: exit: %s: numeric argument required\n", data);
			free_shell(exec->shell);
			exec->shell->status = 2;
			return (1);
		}
		j++;
	}
	return (0);
}

int	builtin_exit(t_exec *exec)
{
	int	i;
	int	result;

	i = 0;
	while (exec->current->command[i])
		i++;
	if (i == 1)
	{
		printf("exit\n");
		free_shell(exec->shell);
		rl_clear_history();
		exit(exec->shell->status);
	}
	if (i > 2)
	{
		if (arg_is_digit(exec) != 0)
			exit(exec->shell->status);
		else
		{
			printf("exit\n");
			write_fd("exit", NULL, "too many arguments", 2);
			return (1);
		}
	}
	if (i == 2)
	{
		if (arg_is_digit(exec) != 0)
			exit(exec->shell->status);
		result = ft_atoi(exec->current->command[1]);
		exec->shell->status = check_overflow(result);
		free_shell(exec->shell);
		rl_clear_history();
		exit (exec->shell->status);
	}
	return (1);
}
