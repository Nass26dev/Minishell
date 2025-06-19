/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:58:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/19 17:35:08 by nyousfi          ###   ########.fr       */
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
	if (!node)
		return ;
	if (node->tag == TOKEN_CMD || (node->tag >= TOKEN_REDIR_IN && node->tag <= TOKEN_APPEND))
	{
		free(node->command[0]);
		free(node->command[1]);
	}
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}
