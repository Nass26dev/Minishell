/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:23:30 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 14:24:23 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	delete_node(t_token **head, t_token *node_to_delete)
{
	t_token	*prev;

	if (!head || !*head || !node_to_delete)
		return ;
	if (*head == node_to_delete)
	{
		*head = node_to_delete->next;
		free(node_to_delete->value);
		free(node_to_delete);
		return ;
	}
	prev = *head;
	while (prev && prev->next != node_to_delete)
		prev = prev->next;
	if (prev && prev->next == node_to_delete)
	{
		prev->next = node_to_delete->next;
		free(node_to_delete->value);
		free(node_to_delete);
	}
}

void	switch_nodes(t_token *a, t_token *b)
{
	t_tag	tmp_tag;
	char	*tmp_value;
	bool	tmp_space;

	if (!a || !b)
		return ;
	tmp_tag = a->tag;
	tmp_value = a->value;
	tmp_space = a->space;
	a->tag = b->tag;
	a->value = b->value;
	a->space = b->space;
	b->tag = tmp_tag;
	b->value = tmp_value;
	b->space = tmp_space;
}
