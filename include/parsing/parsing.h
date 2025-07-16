/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:49:41 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/16 12:59:21 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# ifndef PROMPT
#  define PROMPT "\033[0;35mMinishell$\033[0m "
# endif
# ifndef BASE_FILENAME
#  define BASE_FILENAME "/tmp/heredoc"
# endif
# ifndef MAX_TRIES
#  define MAX_TRIES INT_MAX
# endif

typedef struct s_token
{
	t_tag			tag;
	char			*value;
	char			**cmd;
	bool			space;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	t_token			*tokens;
	t_ast			*ast;
	t_hd			*heredoc;
	t_shell			*shell;
	bool			error;
}					t_data;

typedef struct s_token_sort
{
	t_token			*current;
	t_token			*prev;
	t_token			*redir_start;
	t_token			*redir_end;
	t_token			*after;
	t_token			*reversed;
}					t_token_sort;

typedef struct s_expand
{
	char			*varname;
	char			*varvalue;
	char			*beforevar;
	char			*aftervar;
}					t_expand;

typedef struct s_token_redir
{
	t_token			*current;
	t_token			*prev;
	t_token			*redir_start;
	t_token			*redir_end;
	t_token			*reversed;
}					t_token_redir;

typedef struct s_triple_index
{
	int				i;
	int				j;
	int				y;
}					t_triple_index;

typedef struct s_double_index
{
	int				start;
	int				end;
}					t_double_index;

/*loop_utils.c*/
bool				is_error(bool *error);
t_tag				find_correct_tag(char c);
bool				is_only_quotes(char *input);
bool				is_only_spaces(char *input);

/*line.c*/
int					get_input_and_add_to_historical(char **input);
int					extract_quoted_string(t_data *data, char *input, int i);
int					extract_variable(t_data *data, const char *input, int i);
int					extract_word(t_data *data, const char *input, int i);
int					extract_space(t_data *data, const char *input, int i);

/*error_type.c*/
bool				check_redir_error(char *input, t_data *data);

/*error_checker.c*/
void				error_checker(t_data *data);
void				syntax_error(t_data *data, char *error);
void				print_correct_error(t_tag tag, t_data *data);
void				malloc_error(t_data *data);

/*loop.c*/
bool				else_case(char *input, int *index, t_data *data);

/*lexer.c*/
void				lexer(t_data *data, char *input);

/*extract utils_2.c*/
int					extract_operator(t_data *data, const char *input, int i);

/*parser_utils.c*/
t_token				*find_main_operator(t_token *start, t_token *end);
int					get_operator_priority(t_tag tag);
t_token				*find_prev(t_token *node, t_token *lst);

/*parser.c*/
t_ast				*parser(t_data *data, t_token *start, t_token *end);

/*ast.c*/
t_ast				*create_ast_node(t_tag tag, char *value, char **cmd);
void				free_ast(t_ast *node);
void				print_ast(t_ast *node, int depth);

/*extract_utils.c*/
int					redir_in_heredoc(t_data *data, const char *input, int i);
int					redir_out_append(t_data *data, const char *input, int i);
int					ampersand(t_data *data, char *input, int i);
int					pipe_or(t_data *data, const char *input, int i);

/*case.c*/
int					extract_operator(t_data *data, const char *input, int i);
int					extract_quoted_string(t_data *data, char *input, int i);
int					extract_variable(t_data *data, const char *input, int i);
int					extract_word(t_data *data, const char *input, int i);

/*token.c*/
t_token				*create_token(char *value, t_tag tag);
void				add_token(t_token **head, t_token *new);
void				free_tokens(t_token **head);
void				set_space_to_token(t_token **head);
t_token				*find_last_node(t_token *head);

/*token_utils.c*/
void				switch_nodes(t_token *a, t_token *b);
void				delete_node(t_token **head, t_token *node_to_delete);

/*is.c*/
bool				is_redirection(t_tag tag);
bool				is_var(char *value);

/*utils.c*/
bool				true_exit(t_tag tag, t_data *data);
void				write_fd(char *cmd1, char *cmd2, char *msg, int fd);
void				set_to_null(t_expand *expand);
char				*set_empty(void);
char				*free_strjoin(char *s1, char *s2);
char				*ft_getenv(char *search, char **env);
int					event_hook(void);

/*utils.c*/
char				*ft_strndup(const char *src, size_t n);
bool				ft_isspace(char c);
void				set_to_null(t_expand *expand);
bool				is_operator(char c);
char				*ft_getenv(char *search, char **env);

/*utils2.c*/
bool				char_is_redir(char c);
char				*one_free_strjoin(char *s1, char *s2);

/*expand.c*/
void				expander(t_data *data);
bool				node_is_operator(t_token *node);
bool				node_is_word(t_token *node);
bool				node_is_redir(t_token *node);
void				get_next_value(t_token *current, t_token *next,
						t_data *data);

/*expand_token.c*/
int					expand_token_value(char *input, t_token **token,
						t_data *data);

/*expand_utils2.c*/
t_token				*reverse_token_list(t_token *start, t_token *end);
void				main_sort(t_token_redir *tr, t_token **head);
void				sort_redirections(t_token **head);
void				move_start_redir(t_token **head);
t_token				*delete_empty_node(t_data *data, t_token *tmp);

/*expand_utils.c*/
char				*recup_beforevar(char *input);
char				*recup_varname(char *input);
char				*recup_aftervar(char *input);
char				*recup_varvalue(char *varname, t_data *data);

/*concatenation.c*/
void				concatenate_redirections_args(t_data *data);
void				concatenation(t_data *data);

/*redir_value*/
void				change_redir_value(t_data *data);
void				change_heredoc_value(t_data *data);

/*cmd.c*/
void				create_cmd(t_data *data);

/*extract.c*/
t_token				*split_tokens(char *content);

/*heredoc.c*/
int					change_heredoc(t_data *data);

/*heredoc_creation.c*/
char				*create_file(void);
int					event_hook(void);

#endif