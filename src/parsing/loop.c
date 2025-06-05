/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:58:12 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/05 13:26:12 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void minishell_loop(void)
{
	static t_data data;

	get_line_and_add_to_historical(&data);
	lexer(&data);
	error_checker(&data);
	parser(&data);
}
