/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:53:44 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/18 16:30:18 by eelissal         ###   ########lyon.fr   */
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
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	WORD,
	VARIABLE,
	CMD,
	PIPE,
	AND,
	OR,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	PARENTHESIS,
}	t_tag;

typedef struct s_ast
{
	t_tag			tag;
	t_vector		*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// loop.c
int minishell_loop(void);

/*signal.c*/
void	handle_sigint(int sig);
void	setup_interactive_signals(void);
void	setup_child_signals(void);

/*clean.c*/
void	free_args(char **args);
void	free_ast(t_ast *ast);

/*utils.c*/
void	write_fd(char *cmd1, char *cmd2, char *msg, int fd);

#endif