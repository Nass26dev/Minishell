/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:29:41 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/29 20:57:47 by eelissal         ###   ########lyon.fr   */
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

static void	print_tab_env(char **tab_env, int fd)
{
	int	i;
	int	equal_pos;

	i = 0;
	while (tab_env[i])
	{
		write(fd, "export ", 7);
		equal_pos = 0;
		while (tab_env[i][equal_pos] && tab_env[i][equal_pos] != '=')
			equal_pos++;
		if (tab_env[i][equal_pos] == '=')
		{
			write(fd, tab_env[i], equal_pos + 1);
			write(fd, "\"", 1);
			write(fd, tab_env[i] + equal_pos + 1,
				ft_strlen(tab_env[i] + equal_pos + 1));
			write(fd, "\"", 1);
		}
		else
			write(fd, tab_env[i], ft_strlen(tab_env[i]));
		write(fd, "\n", 1);
		free(tab_env[i++]);
	}
}

static int	display_sorted_var(t_vector *env, int fd)
{
	char	**tab_env;

	if (init_tab_env(&tab_env, env) != 0)
		return (1);
	sort_tab_env(tab_env);
	print_tab_env(tab_env, fd);
	free(tab_env);
	return (0);
}

int	builtin_export(t_exec *exec)
{
	int	ret;
	int	i;

	i = 0;
	while (exec->current->command[i])
		i++;
	if (i == 1)
	{
		ret = display_sorted_var(exec->shell->env, exec->outfd);
		if (ret != 0)
			write_fd("export", NULL, "env cannot be displayed", 2);
	}
	else
	{
		i = 1;
		while (exec->current->command[i])
		{
			ret = export_var(exec->shell->env, exec->current->command[i]);
			i++;
		}
	}
	return (ret);
}
