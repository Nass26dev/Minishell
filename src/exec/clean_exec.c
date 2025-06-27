/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:37:22 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/27 13:38:08 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	unlink_heredoc(t_vector *vector)
{
	int	i;

	if (!vector)
		return ;
	if (vector->data)
	{
		i = 0;
		while (i < vector->count)
		{
			if (vector->data[i])
			{
				unlink(vector->data[i]);
				free(vector->data[i]);
			}
			i++;
		}
		free(vector->data);
	}
	free(vector);
}

void	free_exec(t_exec *exec)
{
	if (exec->shell)
		free_shell(exec->shell);
	if (exec->root)
		free_ast(exec->root);
	if (exec->heredoc)
		unlink_heredoc(exec->heredoc);
}

void	free_all(t_exec *exec)
{
	if (exec->shell)
		free_shell(exec->shell);
	if (exec->root)
		free_ast(exec->root);
	if (exec->heredoc)
		unlink_heredoc(exec->heredoc);
	rl_clear_history();
}
