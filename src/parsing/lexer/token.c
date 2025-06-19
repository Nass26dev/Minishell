/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:55:03 by nass              #+#    #+#             */
/*   Updated: 2025/06/19 15:41:45 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_tokens(t_token **head)
{
	t_token	*next;
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}

t_token	*create_token(char *value, t_type tag)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->tag = tag;
	new->space = false;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!new)
	{
		free_tokens(head);
		printf("malloc error\n");
		exit(1);
	}
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	set_space_to_token(t_token **head)
{
	t_token	*last;

	last = *head;
	while (last->next)
		last = last->next;
	last->space = true;
}

t_token	*find_last_node(t_token *head)
{
	t_token	*current;

	current = head;
	while (current->next)
		current = current->next;
	return (current);
}
