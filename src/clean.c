/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:58:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/26 16:25:34 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void free_ast(t_ast *node)
{
	int i;

	i = 0;
	if (!node)
		return ;
	if (node->tag == TOKEN_CMD || (node->tag >= TOKEN_REDIR_IN && node->tag <= TOKEN_APPEND))
	{
		if (node->command)
		{
			while (node->command[i])
				free(node->command[i++]);
			free(node->command);
		}
	}
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}
