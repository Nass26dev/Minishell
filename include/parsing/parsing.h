/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:49:41 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/05 15:51:17 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

typedef struct s_data
{
	
}			t_data;

// loop.c
void minishell_loop(void);
// line.c
char *get_line_and_add_to_historical(t_data *data);
// error_checker.c
void error_checker(t_data *data);
// lexer.c
void lexer(t_data *data);
// parser.c
void parser(t_data *data);

#endif
