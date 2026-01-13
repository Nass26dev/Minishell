/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:50:42 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/24 13:25:27 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_identifier(char **name)
{
	int	j;

	j = 0;
	if (!(*name)[j])
		return (2);
	while ((*name)[j])
	{
		if (ft_isdigit((*name)[0]))
			return (1);
		if (!ft_isalnum((*name)[j]) && (*name)[j] != '_')
			return (1);
		j++;
	}
	return (0);
}

int	extract_var_name(char **name, char *var)
{
	int		i;

	i = 0;
	if (ft_strchr(var, '=') == 0)
	{
		*name = ft_strdup(var);
		if (*name)
			return (check_identifier(name));
	}
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

int	extract_var_value(char **value, char *var)
{
	int		var_len;
	int		i;

	i = 0;
	var_len = ft_strlen(var);
	if (var_len < 0)
		return (1);
	if (ft_strchr(var, '=') == 0)
		return (0);
	while (var[i])
	{
		if (var[i] == '=')
		{
			*value = ft_substr(var, i + 1, var_len - i - 1);
			if (value)
				return (0);
		}
		i++;
	}
	return (1);
}

static int	invalid_identifier(char *name, int ret)
{
	if (ret == 2)
		write_fd("export", "=", "not a valid identifier", 2);
	else
	{
		write_fd("export", name, "not a valid identifier", 2);
		free(name);
	}
	return (1);
}

int	export_var(t_vector *env, char *var)
{
	char	*name;
	char	*value;
	int		ret;

	name = NULL;
	ret = extract_var_name(&name, var);
	if (ret != 0)
		return (invalid_identifier(name, ret));
	value = NULL;
	if (ret == 0)
		ret = extract_var_value(&value, var);
	if (name && ret == 0)
	{
		ret = add_env_var(env, name, value);
		if (ret != 0)
			write_fd("export", name, "not exported", 2);
	}
	free(name);
	if (value)
		free(value);
	return (ret);
}
