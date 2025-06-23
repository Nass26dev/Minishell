/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:24:29 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/20 12:31:57 by eelissal         ###   ########lyon.fr   */
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
		if (ft_strncmp(line, var, var_len) == 0
			&& (line[var_len] == '=' || line[var_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

bool	get_new_entry(char **new_entry, char *name, char *value)
{
	char	*tmp;

	if (value)
	{
		tmp = ft_strjoin(name, "=");
		if (!tmp)
			return (false);
		*new_entry = ft_strjoin(tmp, value);
		free(tmp);
	}
	else
		*new_entry = ft_strdup(name);
	return (true);
}

int	add_env_var(t_vector *env, char *name, char *value)
{
	char	*new_entry;
	int		i;

	i = find_env_var_index(env, name);
	if (get_new_entry(&new_entry, name, value) == false)
		return (1);
	if (!new_entry)
		return (1);
	if (i >= 0)
	{
		if (value)
		{
			free(env->data[i]);
			env->data[i] = ft_strdup(new_entry);
		}
	}
	else
		vector_add(env, new_entry);
	free(new_entry);
	return (0);
}
