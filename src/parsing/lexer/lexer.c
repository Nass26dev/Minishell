/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:05:03 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/07 00:33:42 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void lexer(t_data *data, char *input)
{
	int i;

	i = 0;
	while (input[i] != 0)
	{
		if (data->error == true)
			return ;
		if (ft_isspace(input[i]))
		{
			set_space_to_token(&data->tokens);
			i++;
		}
		else if (is_operator(input[i]))
			i += extract_operator(data, input, i);
		else if (input[i] == '\'' || input[i] == '"')
			i += extract_quoted_string(data, input, i);
		else if (input[i] == '$')
			i += extract_variable(data, input, i);
		else
			i += extract_word(data, input, i);
	}
}
