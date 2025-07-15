/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:58:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/15 16:44:01 by nass             ###   ########.fr       */
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

void	free_ast(t_ast *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	if (node->tag == CMD || (node->tag >= REDIR_IN
			&& node->tag <= APPEND))
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

void free_heredoc(t_hd_token **heredoc)
{
	t_hd_token	*current;
	t_hd_token	*next;

	if (!heredoc || !*heredoc)
		return ;
	current = *heredoc;
	while (current)
	{
		next = current->next;
		unlink(current->filename);
		free(current->filename);
		free(current);
		current = next;
	}
	*heredoc = NULL;
}
