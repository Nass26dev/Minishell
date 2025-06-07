/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:53:44 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/07 18:47:05 by codespace        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include "libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "env.h"

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
	AST_SEPARATOR,
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

/*signal.c*/
void	handle_sigint(int sig);
void	setup_interactive_signals(void);
void	setup_child_signals(void);

/*clean.c*/
void	free_args(char **args);
void	free_ast(t_ast *ast);

#endif