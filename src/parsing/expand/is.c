/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:25:46 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 17:41:11 by nyousfi          ###   ########.fr       */
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
	return (tag == REDIR_IN || tag == REDIR_OUT
		|| tag == APPEND || tag == HEREDOC);
}
