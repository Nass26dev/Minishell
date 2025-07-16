/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:10:42 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/29 21:14:54 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(t_exec *exec, int i)
{
	int	len;

	while (exec->current->command[i])
		i++;
	if (i > 1)
	{
		write_fd("env", NULL, "too many arguments", STDERR_FILENO);
		return (1);
	}
	i = 0;
	while (i < exec->shell->env->count)
	{
		if (exec->shell->env->data[i] != NULL
			&& ft_strchr(exec->shell->env->data[i], '=') != NULL)
		{
			len = ft_strlen(exec->shell->env->data[i]);
			if (len > 0)
			{
				write(exec->outfd, exec->shell->env->data[i], len);
				write(exec->outfd, "\n", 1);
			}
		}
		i++;
	}
	return (0);
}
