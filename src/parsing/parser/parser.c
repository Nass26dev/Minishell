/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:04:43 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 16:28:02 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_ast_node_on_error(t_data *data, t_ast *node, t_ast *left)
{
	int	i;

	if (left)
	{
		i = 0;
		while (left->command && left->command[i])
			free(left->command[i++]);
		free(left->command);
		free(left);
	}
	if (node)
	{
		i = 0;
		while (node->command && node->command[i])
			free(node->command[i++]);
		free(node->command);
		free(node);
	}
	free_ast(data->ast);
	malloc_error(data);
}

t_ast	*build_operator_node(t_data *data, t_token *start, t_token *end,
		t_token *op)
{
	t_ast	*node;

	node = create_ast_node(op->tag, op->value, op->cmd);
	if (!node)
	{
		free_ast(data->ast);
		malloc_error(data);
	}
	node->left = parser(data, start, find_prev(op, start));
	if (!node->left)
		free_ast_node_on_error(data, node, NULL);
	if (op->tag == TOKEN_REDIR_IN || op->tag == TOKEN_REDIR_OUT
		|| op->tag == TOKEN_APPEND || op->tag == TOKEN_HEREDOC)
		node->right = NULL;
	else
	{
		node->right = parser(data, op->next, end);
		if (!node->right)
			free_ast_node_on_error(data, node, node->left);
	}
	return (node);
}

t_ast	*parser(t_data *data, t_token *start, t_token *end)
{
	t_token	*main_op;

	main_op = find_main_operator(start, end);
	if (main_op && start && end && start != end)
		return (build_operator_node(data, start, end, main_op));
	if (start && start->tag == TOKEN_CMD)
		return (create_ast_node(start->tag, start->value, start->cmd));
	if (start == end)
		return (create_ast_node(start->tag, start->value, start->cmd));
	if (end && !start)
		return (create_ast_node(end->tag, end->value, end->cmd));
	return (NULL);
}
