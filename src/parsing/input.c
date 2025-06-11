/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:03:10 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/11 14:01:43 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int get_input_and_add_to_historical(char **input)
{	
	*input = readline(PROMPT);
	if (*input == NULL)
	{
		printf("exit\n");
		return (1);
	}
	if (*input && *input[0] != 0)
		add_history(*input);
	return (0);
}
