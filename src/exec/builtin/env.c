/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:10:42 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/14 13:59:21 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->current->cmd->count > 1)
	{
		ft_putstr_fd("minishell: env function cannot take any options or arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (i < exec->shell->env->count)
	{
		if (exec->shell->env->data[i] != NULL)
			printf("%s\n", exec->shell->env->data[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
