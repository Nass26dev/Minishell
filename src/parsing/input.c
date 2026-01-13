/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:03:10 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/16 08:58:40 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_input_and_add_to_historical(char **input)
{
	*input = readline(PROMPT);
	if (*input == NULL)
	{
		printf("exit\n");
		return (1);
	}
	if (g_received_signal == SIGINT)
	{
		if (*input && *input[0] != 0)
			add_history(*input);
		return (2);
	}
	if (*input && *input[0] != 0)
		add_history(*input);
	return (0);
}
