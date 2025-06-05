/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:58:12 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/05 12:52:37 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing/parsing.h"

void minishell_loop(void)
{
	static t_data data;

	get_line_and_add_to_historical(&data);
	lexer(&data);
	error_checker(&data);
	parser(&data);
}
