/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_is.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:21:54 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 14:22:06 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	node_is_redir(t_token *node)
{
	if (!node)
		return (false);
	return (node->tag == TOKEN_REDIR_IN || node->tag == TOKEN_REDIR_OUT
		|| node->tag == TOKEN_APPEND || node->tag == TOKEN_HEREDOC);
}

bool	node_is_word(t_token *node)
{
	if (!node)
		return (false);
	return (node->tag == TOKEN_SINGLE_QUOTE || node->tag == TOKEN_DOUBLE_QUOTE
		|| node->tag == TOKEN_WORD);
}

bool	node_is_operator(t_token *node)
{
	if (!node)
		return (false);
	return (node->tag == TOKEN_PIPE || node->tag == TOKEN_OR
		|| node->tag == TOKEN_AND);
}
