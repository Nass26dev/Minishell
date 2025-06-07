/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:03:10 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/07 16:19:51 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void get_input_and_add_to_historical(t_data *data, char **input)
{	
	(void)data;
	*input = NULL;
	*input = readline(PROMPT);
	if (*input && *input[0] != 0)
		add_history(*input);
}
