/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:10:42 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/11 14:17:55 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_env(t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->current->cmd->count > 1)
	{
		printf("minishell: env function cannot take any options or arguments\n");
		return (2);
	}
	while (i < exec->shell->env->count)
	{
		if (exec->shell->env->data[i] != NULL)
			printf("%s\n", exec->shell->env->data[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
