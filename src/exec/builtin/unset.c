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

int	find_env_var_index(t_vector *env, char *var)
{
	size_t	var_len;
	int		i;
	char	*line;

	if (!env || !var)
		return (-1);
	var_len = ft_strlen(var);
	i = 0;
	while (i < env->count)
	{
		line = env->data[i];
		if (ft_strncmp(line, var, var_len) == 0 && line[var_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

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
