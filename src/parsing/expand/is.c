/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:25:46 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 14:25:54 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_var(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] && !ft_isspace(value[i + 1]))
			return (true);
		i++;
	}
	return (false);
}

bool	is_redirection(t_tag tag)
{
	return (tag == TOKEN_REDIR_IN || tag == TOKEN_REDIR_OUT
		|| tag == TOKEN_APPEND || tag == TOKEN_HEREDOC);
}
