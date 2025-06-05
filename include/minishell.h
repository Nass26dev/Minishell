/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:53:44 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/05 12:05:49 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "stdio.h"
# include "stdlib.h"
# include "stdbool.h"
# include <limits.h>
# include <unistd.h>

typedef struct s_vector
{
	char	**data;
	int		count;
	int		capacity;
}	t_vector;

typedef struct s_shell
{
	t_vector	*env;
	int			status;
}	t_shell;

typedef struct s_data
{
	
}			t_data;

typedef enum e_tag
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_REDIR_IN,
	AST_REDIR_OUT,
	AST_HEREDOC,
	AST_APPEND,
	AST_PARENTHESIS,
}	t_tag;

typedef struct s_ast
{
	t_tag			tag;
	t_vector		*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// loop.c
void minishell_loop(void);
// line.c
char *get_line_and_add_to_historical(t_data *data);
// error_checker.c
void error_checker(t_data *data);

#endif