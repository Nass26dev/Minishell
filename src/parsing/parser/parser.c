/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:04:43 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/20 23:26:47 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_operator_priority(t_tag tag)
{
	if (tag == TOKEN_OR)
		return (1);
	if (tag == TOKEN_AND)
		return (2);
	if (tag == TOKEN_PIPE)
		return (3);
	if (tag == TOKEN_REDIR_IN)
		return (4);
	if (tag == TOKEN_REDIR_OUT)
		return (4);
	if (tag == TOKEN_APPEND)
		return (4);
	if (tag == TOKEN_HEREDOC)
		return (4);
	return (100);
}

t_token	*find_main_operator(t_token *start, t_token *end)
{
	t_token	*current;
	t_token	*main_op;
	int		min_prio;
	int		priority;

	current = start;
	main_op = NULL;
	min_prio = 100;
	while (current)
	{
		priority = get_operator_priority(current->tag);
		if (priority == 3 || priority == 4)
		{
			if (priority < min_prio || (priority == min_prio && priority < 5))
			{
				min_prio = priority;
				main_op = current;
			}
		}
		else
		{
			if (priority < min_prio)
			{
				min_prio = priority;
				main_op = current;
			}
		}
		if (current == end)
			break ;
		current = current->next;
	}
	return (main_op);
}

t_token	*find_prev(t_token *node, t_token *lst)
{
	t_token	*current;

	if (!node || !lst || node == lst)
		return (NULL);
	current = lst;
	while (current && current->next)
	{
		if (current->next == node)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_ast	*parser(t_data *data, t_token *start, t_token *end)
{
	t_token	*main_op;
	t_ast	*node;

	main_op = find_main_operator(start, end);
	if (main_op && start && end && start != end)
	{
		node = create_ast_node(main_op->tag, main_op->value, main_op->cmd);
		if (main_op->tag == TOKEN_REDIR_IN || main_op->tag == TOKEN_REDIR_OUT
			|| main_op->tag == TOKEN_APPEND || main_op->tag == TOKEN_HEREDOC)
		{
			node->left = parser(data, start, find_prev(main_op, start));
			node->right = NULL;
		}
		else
		{
			node->left = parser(data, start, find_prev(main_op, start));
			node->right = parser(data, main_op->next, end);
		}
		return (node);
	}
	if (start->tag == TOKEN_CMD)
		return (create_ast_node(start->tag, start->value, start->cmd));
	if (start == end)
		return (create_ast_node(start->tag, start->value, start->cmd));
	if (end && !start)
		return (create_ast_node(end->tag, end->value, end->cmd));
	return (NULL);
}
