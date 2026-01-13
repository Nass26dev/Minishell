/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:12:06 by nass              #+#    #+#             */
/*   Updated: 2025/06/30 15:20:05 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	should_concatenate(t_token *current, t_token *next)
{
	if (!current || !next)
		return (false);
	if (next->tag != WORD && next->tag != DOUBLE_QUOTE
		&& next->tag != SINGLE_QUOTE && next->tag != VARIABLE)
		return (false);
	return (true);
}

int	concatenate_nodes(t_token *current, t_token *next)
{
	char	*new_value;
	t_token	*tmp;
	size_t	len_current;
	size_t	len_next;
	size_t	total_len;

	if (!should_concatenate(current, next))
		return (0);
	len_current = ft_strlen(current->value);
	len_next = ft_strlen(next->value);
	total_len = (len_current + len_next) + 1;
	new_value = malloc(total_len);
	if (!new_value)
		return (1);
	ft_strlcpy(new_value, current->value, total_len);
	ft_strlcat(new_value, next->value, total_len);
	free(current->value);
	current->value = new_value;
	current->tag = WORD;
	current->space = next->space;
	tmp = next->next;
	free(next->value);
	free(next);
	current->next = tmp;
	return (0);
}

void	skip_redir(t_token **node, bool cmd, t_token **last_redir)
{
	t_token	*current;

	current = *node;
	while (node_is_redir(current))
	{
		if (!cmd)
			current = current->next;
		else
		{
			current = current->next;
			*last_redir = current;
		}
	}
}

void	concatenation(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if ((current->tag == SINGLE_QUOTE
				|| current->tag == DOUBLE_QUOTE
				|| current->tag == VARIABLE || current->tag == WORD)
			&& !current->space)
		{
			if (concatenate_nodes(current, current->next))
				malloc_error(data);
		}
		if ((current->tag == SINGLE_QUOTE
				|| current->tag == DOUBLE_QUOTE
				|| current->tag == VARIABLE || current->tag == WORD)
			&& current->space == 0 && should_concatenate(current,
				current->next))
			continue ;
		current = current->next;
	}
}

void	concatenate_redirections_args(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (node_is_redir(tmp) && tmp->next && !tmp->space)
		{
			tmp->value = one_free_strjoin(tmp->value, tmp->next->value);
			if (!tmp->value)
				malloc_error(data);
			tmp->space = tmp->next->space;
			delete_node(&data->tokens, tmp->next);
		}
		else
			tmp = tmp->next;
	}
}
