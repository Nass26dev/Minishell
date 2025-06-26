/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:55:03 by nass              #+#    #+#             */
/*   Updated: 2025/06/26 14:56:19 by nass             ###   ########.fr       */
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

t_token	*create_token(char *value, t_tag tag)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
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

	if (!*head)
		return ;
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
