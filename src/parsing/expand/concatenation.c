/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:12:06 by nass              #+#    #+#             */
/*   Updated: 2025/06/19 16:18:11 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	should_concatenate(t_token *current, t_token *next)
{
	if (!current || !next)
		return (false);
	if (next->tag != TOKEN_WORD && next->tag != TOKEN_DOUBLE_QUOTE
		&& next->tag != TOKEN_SINGLE_QUOTE && next->tag != TOKEN_VARIABLE)
		return (false);
	return (true);
}

void	concatenate_nodes(t_token *current, t_token *next)
{
	char	*new_value;
	t_token	*tmp;
	size_t	len_current;
	size_t	len_next;
	size_t	total_len;

	if (!should_concatenate(current, next))
		return ;
	len_current = ft_strlen(current->value);
	len_next = ft_strlen(next->value);
	total_len = (len_current + len_next) + 1;
	new_value = malloc(total_len);
	ft_strlcpy(new_value, current->value, total_len);
	ft_strlcat(new_value, next->value, total_len);
	free(current->value);
	current->value = new_value;
	current->tag = TOKEN_WORD;
	current->space = next->space;
	tmp = next->next;
	free(next->value);
	free(next);
	current->next = tmp;
}

void	concatenate_nodes_with_spaces(t_token *current, t_token *next)
{
	char	*new_value;
	t_token	*tmp;
	size_t	len_current;
	size_t	len_next;
	size_t	total_len;

	if (!should_concatenate(current, next))
		return ;
	len_current = ft_strlen(current->value);
	len_next = ft_strlen(next->value);
	total_len = (len_current + len_next) + 2;
	new_value = malloc(total_len);
	ft_strlcpy(new_value, current->value, total_len);
	ft_strlcat(new_value, " ", total_len);
	ft_strlcat(new_value, next->value, total_len);
	free(current->value);
	current->value = new_value;
	current->tag = TOKEN_WORD;
	current->space = next->space;
	tmp = next->next;
	free(next->value);
	free(next);
	current->next = tmp;
}

void	concatenate_nodes_after_redir(t_token *current, t_token *saved,
		t_token *last_dir)
{
	char	*new_value;
	t_token	*tmp;
	size_t	len_saved;
	size_t	len_current;
	size_t	total_len;

	if (!should_concatenate(saved, current))
		return ;
	len_saved = ft_strlen(saved->value);
	len_current = ft_strlen(current->value);
	total_len = (len_saved + len_current) + 2;
	new_value = malloc(total_len);
	ft_strlcpy(new_value, saved->value, total_len);
	ft_strlcat(new_value, " ", total_len);
	ft_strlcat(new_value, current->value, total_len);
	free(saved->value);
	saved->value = new_value;
	saved->tag = TOKEN_WORD;
	saved->space = current->space;
	tmp = current->next;
	free(current->value);
	free(current);
	last_dir->next = tmp;
}

void skip_redir(t_token **node, bool cmd, t_token **last_redir)
{
	t_token *current;

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

// void manage_words(t_token **current, bool is_saved, t_token **saved, t_token **last_redir)
// {
// 	if (node_is_word(current) && !is_saved)
// 	{
// 		if (node_is_word(current->next))
// 		{
// 			concatenate_nodes_with_spaces(current, current->next);
// 			continue ;
// 		}
// 		else if (node_is_redir(current->next))
// 		{
// 			saved = current;
// 			is_saved = true;
// 			current = current->next;
// 			while (node_is_redir(current))
// 			{
// 				last_redir = current;
// 				current = current->next;
// 			}
// 		}
// 	}
// }
void	concatenate_args(t_data *data)
{
	t_token	*current;
	t_token	*saved;
	t_token	*last_redir;
	bool	is_saved;
	bool	cmd;

	current = data->tokens;
	while (current)
	{
		cmd = false;
		is_saved = false;
		while (current && !node_is_operator(current))
		{
			skip_redir(&current, cmd, &last_redir);
			if (node_is_word(current) && !cmd)
			{
				cmd = true;
				current = current->next;
			}
			if (node_is_word(current) && !is_saved)
			{
				if (node_is_word(current->next))
				{
					concatenate_nodes_with_spaces(current, current->next);
					continue ;
				}
				else if (node_is_redir(current->next))
				{
					saved = current;
					is_saved = true;
					current = current->next;
					while (node_is_redir(current))
					{
						last_redir = current;
						current = current->next;
					}
				}
			}
			if (node_is_word(current) && is_saved)
			{
				concatenate_nodes_after_redir(current, saved, last_redir);
				is_saved = false;
				continue ;
			}
			if (current)
				current = current->next;
			else
				break ;
		}
		if (node_is_operator(current))
			current = current->next;
	}
}

void	concatenation(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if ((current->tag == TOKEN_SINGLE_QUOTE
				|| current->tag == TOKEN_DOUBLE_QUOTE
				|| current->tag == TOKEN_VARIABLE || current->tag == TOKEN_WORD)
			&& !current->space)
			concatenate_nodes(current, current->next);
		if ((current->tag == TOKEN_SINGLE_QUOTE
				|| current->tag == TOKEN_DOUBLE_QUOTE
				|| current->tag == TOKEN_VARIABLE || current->tag == TOKEN_WORD)
			&& current->space == 0 && should_concatenate(current,
				current->next))
			continue ;
		current = current->next;
	}
	concatenate_args(data);
}
