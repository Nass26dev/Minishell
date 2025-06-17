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

int	find_var_index_in_env(t_vector *env, char *var)
{
	size_t	var_len;
	int		i;
	char	*entry;

	if (!env || !var)
		return (-1);
	var_len = ft_strlen(var);
	i = 0;
	while (i < env->count)
	{
		entry = env->data[i];
		if (ft_strncmp(entry, var, var_len) == 0 && entry[var_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	remove_env_var(t_vector *env, char *var)
{
	int	i;

	i = find_var_index_in_env(env, var);
	if (i == -1)
		return (EXIT_FAILURE);
	free(env->data[i]);
	while (i < env->count - 1)
	{
		env->data[i] = env->data[i + 1];
		i++;
	}
	env->count--;
	env->data[env->count] = NULL;
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_exec *exec)
{
	int	i;

	if (!exec->shell->env)
		return (EXIT_FAILURE);
	i = 1;
	while (exec->current->cmd->data[i])
	{
		if (exec->current->cmd->data[i][0] == '-')
		{
			write_fd("unset", "options are not supported", STDERR_FILENO);
			return (1);
		}
		remove_env_var(exec->shell->env, exec->current->cmd->data[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
