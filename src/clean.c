/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:58:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/19 15:52:54 by nyousfi          ###   ########.fr       */
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

// void	free_ast(t_ast *ast)
// {
// 	if (!ast)
// 		return ;
// 	if (ast->cmd)
// 		free_vector(ast->cmd);
// 	if (ast->left)
// 		free_ast(ast->left);
// 	if (ast->right)
// 		free_ast(ast->right);
// 	free(ast);
// }
