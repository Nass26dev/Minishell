/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:29:41 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/20 10:23:29 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	add_env_var(t_vector *env, char *name, char *value)
{
	char	*new_entry;
	char	*tmp;
	int		i;

	i = find_env_var_index(env, name);
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (1);
	new_entry = ft_strjoin(tmp, value);
	free(tmp);
	if (!new_entry)
		return (1);
	if (i >= 0)
	{
		free(env->data[i]);
		env->data[i] = ft_strdup(new_entry);
	}
	else
		vector_add(env, new_entry);
	free(new_entry);
	return (0);
}

static int	check_identifier(char **name)
{
	int	j;

	j = 0;
	while ((*name)[j])
	{
		if (!ft_isalnum((*name)[j]) && (*name)[j] != '_')
		{
			write_fd("export", *name, "not a valid identifier", 2);
			free(*name);
			return (1);
		}
		j++;
	}
	return (0);
}

static int	extract_var_name(char **name, char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			*name = ft_substr(var, 0, i);
			if (*name)
				return (check_identifier(name));
		}
		i++;
	}
	return (1);
}

static int	extract_var_value(char **value, char *var)
{
	int		var_len;
	int		i;

	i = 0;
	var_len = ft_strlen(var);
	if (var_len < 0)
		return (1);
	while (var[i])
	{
		if (var[i] == '=')
		{
			*value = ft_substr(var, i + 1, var_len - i - 1);
			if (*value)
				return (0);
		}
		i++;
	}
	return (1);
}

static int	export_var(t_vector *env, char *var)
{
	char	*name;
	char	*value;
	int		ret;

	name = NULL;
	ret = extract_var_name(&name, var);
	value = NULL;
	if (ret == 0)
		ret = extract_var_value(&value, var);
	if (name && value && ret == 0)
	{
		ret = add_env_var(env, name, value);
		if (ret != 0)
			write_fd("export", name, "not exported", 2);
	}
	if (name)
		free(name);
	if (value)
		free(value);
	return (ret);
}

static int	display_sorted_var(t_vector *env)
{
	// char	**sorted_env;
	// char	*temp;
	// int		i;
	// int		j;
	// int		equal_pos;

	// sorted_env = malloc(sizeof(char *) * (env->size + 1));
	// if (!sorted_env)
	// 	return (1);
	// i = 0;
	// while (i < env->size)
	// {
	// 	sorted_env[i] = ft_strdup(env->data[i]);
	// 	if (!sorted_env[i])
	// 	{
	// 		while (--i >= 0)
	// 			free(sorted_env[i]);
	// 		free(sorted_env);
	// 		return (1);
	// 	}
	// 	i++;
	// }
	// sorted_env[i] = NULL;
	// i = 0;
	// while (sorted_env[i])
	// {
	// 	j = i + 1;
	// 	while (sorted_env[j])
	// 	{
	// 		if (ft_strcmp(sorted_env[i], sorted_env[j]) > 0)
	// 		{
	// 			temp = sorted_env[i];
	// 			sorted_env[i] = sorted_env[j];
	// 			sorted_env[j] = temp;
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	// i = 0;
	// while (sorted_env[i])
	// {
	// 	write(1, "declare -x ", 11);
	// 	equal_pos = 0;
	// 	while (sorted_env[i][equal_pos] && sorted_env[i][equal_pos] != '=')
	// 		equal_pos++;
	// 	if (sorted_env[i][equal_pos] == '=')
	// 	{
	// 		write(1, sorted_env[i], equal_pos + 1);
	// 		write(1, "\"", 1);
	// 		write(1, sorted_env[i] + equal_pos + 1, 
	// 			ft_strlen(sorted_env[i] + equal_pos + 1));
	// 		write(1, "\"", 1);
	// 	}
	// 	else
	// 		write(1, sorted_env[i], ft_strlen(sorted_env[i]));
	// 	write(1, "\n", 1);
	// 	free(sorted_env[i++]);
	// }
	// free(sorted_env);
	(void) env;
	return (0);
}

int	builtin_export(t_shell *shell, char **data)
{
	int	ret;
	int	i;

	i = 0;
	while (data[i])
		i++;
	if (i == 1)
	{
		ret = display_sorted_var(shell->env);
		if (ret != 0)
			write_fd("export", NULL, "env cannot be displayed", 2);
	}
	else
	{
		i = 1;
		while (data[i])
		{
			ret = export_var(shell->env, data[i]);
			if (ret != 0)
				write_fd("export", data[i], "was not exported", 2);
			i++;
		}
	}
	return (ret);
}
