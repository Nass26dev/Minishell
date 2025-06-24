/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:03:10 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/24 16:49:49 by nyousfi          ###   ########.fr       */
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
		return (1);
	if (*input && *input[0] != 0)
		add_history(*input);
	return (0);
}
