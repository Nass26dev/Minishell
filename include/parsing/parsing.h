/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:49:41 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/06 17:20:56 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "../minishell.h"

#define PROMPT "\033[0;35mMinishell$\033[0m "

typedef enum e_tag
{
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_VARIABLE
}			t_tag;

typedef struct s_token
{
	t_tag tag;
	char *value;
	struct s_token *next;
}			t_token;

typedef struct s_data
{
	t_token *tokens;
	bool error;
}			t_data;

// loop.c
void minishell_loop(void);
// line.c
void get_input_and_add_to_historical(t_data *data, char **input);
// error_checker.c
void error_checker(t_data *data);
void syntax_error(t_data *data, char *error);
// lexer.c
void lexer(t_data *data, char *input);
// parser.c
void parser(t_data *data);
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
t_token *create_token(char *value, t_tag tag);
void add_token(t_token **head, t_token *new);
void free_tokens(t_token **head);
// utils.c
char *ft_strndup(const char *src, size_t n);
bool ft_isspace(char c);
bool is_operator(char c);
char	*ft_strdup(char *src);
int ft_isalnum(int c);
size_t ft_strlen(const char *str);

#endif


