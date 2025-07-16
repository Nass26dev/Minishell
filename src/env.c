/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:58:13 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/15 19:03:53 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_shell(t_shell *shell, char **envp)
{
	int		i;

	shell->status = 0;
	shell->env = vector_create(1);
	if (!shell->env)
		return (false);
	shell->env->count = 0;
	shell->env->capacity = 1;
	i = 0;
	if (!envp)
		return (true);
	while (envp[i])
	{
		if (vector_add(shell->env, envp[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

char	*get_env(t_vector *env, char *to_search)
{
	int	i;
	int	len_to_search;

	i = 0;
	if (!env || !to_search)
		return (NULL);
	len_to_search = ft_strlen(to_search);
	while (i < env->count)
	{
		if (ft_strncmp(env->data[i], to_search, len_to_search) == 0
			&& env->data[i][len_to_search] == '=')
			return (ft_strdup(&(env->data[i][len_to_search + 1])));
		i++;
	}
	return (NULL);
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
		free_vector(shell->env);
}
