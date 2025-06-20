/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:29:41 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/20 12:28:03 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	init_tab_env(char ***tab_env, t_vector *env)
{
	int	i;

	*tab_env = malloc(sizeof(char *) * (env->count + 1));
	if (!*tab_env)
		return (1);
	i = 0;
	while (i < env->count)
	{
		(*tab_env)[i] = ft_strdup(env->data[i]);
		if (!(*tab_env)[i])
		{
			while (--i >= 0)
				free((*tab_env)[i]);
			free(*tab_env);
			return (1);
		}
		i++;
	}
	(*tab_env)[i] = NULL;
	return (0);
}

static void	sort_tab_env(char **tab_env)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (tab_env[i])
	{
		j = i + 1;
		while (tab_env[j])
		{
			if (ft_strcmp(tab_env[i], tab_env[j]) > 0)
			{
				temp = tab_env[i];
				tab_env[i] = tab_env[j];
				tab_env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_tab_env(char **tab_env)
{
	int	i;
	int	equal_pos;

	i = 0;
	while (tab_env[i])
	{
		write(1, "export ", 7);
		equal_pos = 0;
		while (tab_env[i][equal_pos] && tab_env[i][equal_pos] != '=')
			equal_pos++;
		if (tab_env[i][equal_pos] == '=')
		{
			write(1, tab_env[i], equal_pos + 1);
			write(1, "\"", 1);
			write(1, tab_env[i] + equal_pos + 1,
				ft_strlen(tab_env[i] + equal_pos + 1));
			write(1, "\"", 1);
		}
		else
			write(1, tab_env[i], ft_strlen(tab_env[i]));
		write(1, "\n", 1);
		free(tab_env[i++]);
	}
}

static int	display_sorted_var(t_vector *env)
{
	char	**tab_env;

	if (init_tab_env(&tab_env, env) != 0)
		return (1);
	sort_tab_env(tab_env);
	print_tab_env(tab_env);
	free(tab_env);
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
