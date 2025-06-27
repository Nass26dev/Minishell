/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:19:56 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 16:24:53 by nyousfi          ###   ########.fr       */
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

void	update_main_operator(t_token **main_op, int *min_prio, t_token *current,
		int priority)
{
	if (priority == 3 || priority == 4)
	{
		if (priority < *min_prio || (priority == *min_prio && priority < 5))
		{
			*min_prio = priority;
			*main_op = current;
		}
	}
	else
	{
		if (priority < *min_prio)
		{
			*min_prio = priority;
			*main_op = current;
		}
	}
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
		update_main_operator(&main_op, &min_prio, current, priority);
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
