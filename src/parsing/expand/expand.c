/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:18:39 by nass              #+#    #+#             */
/*   Updated: 2025/06/30 19:25:28 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	expand_rest(t_data *data)
{
	change_redir_value(data);
	concatenate_redirections_args(data);
	concatenation(data);
	move_start_redir(&data->tokens);
	sort_redirections(&data->tokens);
	create_cmd(data);
}

void	expander(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	change_heredoc_value(data);
	while (tmp)
	{
		if (tmp->tag == VARIABLE || tmp->tag == DOUBLE_QUOTE
			|| tmp->tag == WORD)
		{
			while (is_var(tmp->value))
			{
				if (expand_token_value(tmp->value, &tmp, data))
					malloc_error(data);
				if (!tmp && !tmp->value[0])
					tmp = delete_empty_node(data, tmp);
			}
			tmp->tag = WORD;
		}
		tmp = tmp->next;
	}
	expand_rest(data);
}
