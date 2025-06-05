/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:49:41 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/05 15:31:25 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#define PROMPT "\033[0;35mMinishell$\033[0m "

typedef enum e_tag
{
	word,
	double_quote,
	simple_quote,
	operator,
	variable,
	separator
}			t_tag;

typedef struct s_token_list
{
	t_tag tag;
	char *value;
	struct s_token_list *next;
}			t_token_list;

typedef struct s_data
{
	t_token_list *lst;
}			t_data;

// loop.c
void minishell_loop(void);
// line.c
void get_input_and_add_to_historical(t_data *data, char **input);
// error_checker.c
void error_checker(t_data *data);
// lexer.c
void lexer(t_data *data, char *input);
// parser.c
void parser(t_data *data);
// read.c
void read_double_quoted_string(t_data *data, char *input, int *i);
void read_simple_quoted_string(t_data *data, char *input, int *i);
void read_variable(t_data *data, char *input, int *i);
void read_operator(t_data *data, char *input, int *i);
void read_word(t_data *data, char *input, int *i);
void read_separator(t_data *data, char *input, int *i);

#endif


