/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_is.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:21:54 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 17:41:11 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	node_is_redir(t_token *node)
{
	if (!node)
		return (false);
	return (node->tag == REDIR_IN || node->tag == REDIR_OUT
		|| node->tag == APPEND || node->tag == HEREDOC);
}

bool	node_is_word(t_token *node)
{
	if (!node)
		return (false);
	return (node->tag == SINGLE_QUOTE || node->tag == DOUBLE_QUOTE
		|| node->tag == WORD);
}

bool	node_is_operator(t_token *node)
{
	if (!node)
		return (false);
	return (node->tag == PIPE || node->tag == OR
		|| node->tag == AND);
}
