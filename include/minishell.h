/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:53:44 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/09 17:54:40 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif

# include "stdio.h"
# include "stdlib.h"
# include "stdbool.h"
# include <limits.h>
# include <unistd.h>
# include "libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

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

#endif