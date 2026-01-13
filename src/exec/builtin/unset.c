/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:07:44 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/17 14:56:53 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	remove_env_var(t_vector *env, char *var)
{
	int	i;

	i = find_env_var_index(env, var);
	if (i == -1)
		return (1);
	free(env->data[i]);
	while (i < env->count - 1)
	{
		env->data[i] = env->data[i + 1];
		i++;
	}
	env->count--;
	env->data[env->count] = NULL;
	return (0);
}

int	builtin_unset(t_exec *exec)
{
	int	i;

	if (!exec->shell->env)
		return (1);
	i = 1;
	while (exec->current->command[i])
	{
		if (exec->current->command[i][0] == '-')
		{
			write_fd("unset", NULL, "options are not supported", STDERR_FILENO);
			return (1);
		}
		remove_env_var(exec->shell->env, exec->current->command[i]);
		i++;
	}
	return (0);
}
