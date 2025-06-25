/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:03:10 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/25 17:15:16 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_input_and_add_to_historical(char **input)
{
	char *prompt;

	prompt = NULL;
	if (isatty(STDIN_FILENO))
		prompt = PROMPT;
	else
		prompt = "";
	*input = readline(PROMPT);
	if (*input == NULL)
	{
		printf("exit\n");
		return (1);
	}
	if (received_signal == SIGINT)
	{
		return (2);
	}
	if (*input && *input[0] != 0)
		add_history(*input);
	return (0);
}
