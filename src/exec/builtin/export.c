/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:29:41 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/18 16:35:39 by eelissal         ###   ########lyon.fr   */
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

static int	extract_var_name(char *name, char *var)
{
	int		i;

	i = 0;
	name = NULL;
	while (var[i])
	{
		if (var[i] == '=')
		{
			name = ft_substr(var, 0, i);
			if (name)
			{
				// if ( != NULL) //strchr > return pointeur to null or to char it found> same but with a set of char instead of just one
					// {
					// 	write_fd("export", name, "not a valid identifier", STDERR_FILENO);
					// 	return (1);
					// }
				return (0);
			}
		}
		i++;
	}
	return (1);
}

static int	extract_var_value(char *value, char *var)
{
	int		var_len;
	int		i;

	i = 0;
	value = NULL;
	var_len = ft_strlen(var);
	if (var_len < 0)
		return (1);
	while (var[i])
	{
		if (var[i] == '=')
		{
			value = ft_substr(var, i + 1, var_len - i - 1);
			if (value)
			{
				// if (str[0] != NULL) //strchr > return pointeur to null or to char it found (str[0])> same but with a set of char instead of just one
					// {
					// 	printf("minishell: syntax error near unexpected token '%c\n'", str[0])
					// 	return (1);
					// }
				return (0);
			}
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
	ret = extract_var_name(name, var);
	value = NULL;
	if (ret == 0)
		ret = extract_var_value(value, var);
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
	//display in a tab : name and entry
	//sort data in the tab
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
		while(data[i])
		{
			ret = export_var(shell->env, data[i]);
			if (ret != 0)
				write_fd("export", data[i], "was not exported", 2);
			i++;
		}
	}
	return (ret);
}
