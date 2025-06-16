/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:04:43 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/16 18:26:40 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_operator_priority(t_type type)
{
	if (type == TOKEN_OR)
		return (1);
	if (type == TOKEN_AND)
		return (2);
	if (type == TOKEN_PIPE)
		return (3);
	if (type == TOKEN_REDIR_IN)
		return (4);
	if (type == TOKEN_REDIR_OUT)
		return (4);
	if (type == TOKEN_APPEND)
		return (4);
	if (type == TOKEN_HEREDOC)
		return (4);
	return (100); // for words/commands
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
		return (NULL); // aucun précédent si node est NULL ou en tête
	current = lst;
	while (current && current->next)
	{
		if (current->next == node)
			return (current);
		current = current->next;
	}
	return (NULL); // node non trouvé ou pas dans la liste
}

t_ast	*parser(t_data *data, t_token *start, t_token *end)
{
	t_token	*main_op;
	t_ast	*node;

    // mettre dans le bon ordre les redirections
	main_op = find_main_operator(start, end);
	if (main_op && start && end && start != end)
	{
		node = create_ast_node(main_op->tag, main_op->value);
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
	if (start && start != end && (start->tag == TOKEN_WORD
			|| start->tag == TOKEN_DOUBLE_QUOTE
			|| start->tag == TOKEN_SINGLE_QUOTE))
	{
		node = create_ast_node(start->tag, start->value);
		if (start->next && (start->next->tag == TOKEN_WORD
				|| start->next->tag == TOKEN_DOUBLE_QUOTE
				|| start->next->tag == TOKEN_SINGLE_QUOTE))
			add_args_to_command(&node, start->next->value);
		return (node);
	}
	if (start == end)
		return (create_ast_node(start->tag, start->value));
	if (end && !start)
		return (create_ast_node(end->tag, end->value));
	return (NULL);
}
