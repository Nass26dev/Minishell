/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:49:41 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/16 13:16:43 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "minishell.h"

#define PROMPT "\033[0;35mMinishell$\033[0m "

typedef struct s_token
{
	t_type tag;
	char *value;
	bool space;
	struct s_token *next;
}			t_token;

typedef struct s_data
{
	t_token *tokens;
	t_ast	*ast;
	t_shell	*shell;
	bool error;
}			t_data;

typedef struct s_expand
{
	char *varname;
	char *varvalue;
	char *beforevar;
	char *aftervar;	
}			t_expand;

// line.c
int get_input_and_add_to_historical(char **input);
// error_checker.c
void error_checker(t_data *data);
void syntax_error(t_data *data, char *error);
void print_correct_error(t_type tag);
// lexer.c
void lexer(t_data *data, char *input);
// parser.c
t_ast *parser(t_data *data, t_token *start, t_token *end);
// ast.c
t_ast *create_ast_node(t_type type, char *value);
void print_ast(t_ast *node, int depth);
void add_args_to_command(t_ast **node, char *args);
// case_utils.c
int redir_in_heredoc(t_data *data, const char *input, int i);
int redir_out_append(t_data *data, const char *input, int i);
int ampersand(t_data *data, char *input, int i);
int pipe_or(t_data *data, const char *input, int i);
// case.c
int extract_operator(t_data *data, const char *input, int i);
int extract_quoted_string(t_data *data, char *input, int i);
int extract_variable(t_data *data, const char *input, int i);
int extract_word(t_data *data, const char *input, int i);
// token.c
t_token *create_token(char *value, t_type tag);
void add_token(t_token **head, t_token *new);
void free_tokens(t_token **head);
void set_space_to_token(t_token **head);
t_token *find_last_node(t_token *head);
// utils.c
char *ft_strndup(const char *src, size_t n);
bool ft_isspace(char c);
bool is_operator(char c);
// expand.c
void expander(t_data *data);
// expand_utils.c
char *recup_beforevar(char *input);
char *recup_varname(char *input);
char *recup_aftervar(char *input);
char *recup_varvalue(char *varname);
// concatenation.c
void concatenation(t_data *data);
// redir_value
void change_redir_value(t_data *data);

#endif