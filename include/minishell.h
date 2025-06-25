/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:53:44 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/25 18:44:32 by nyousfi          ###   ########.fr       */
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

#define BLUE "\033[1;34m"
#define PURPLE "\033[1;35m"
#define RESET "\033[0m"

typedef enum e_tag
{
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_WORD,
	TOKEN_VARIABLE,
	TOKEN_CMD,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_PARENTHESIS,
}	t_tag;

extern int	received_signal;

typedef struct s_ast
{
	t_tag			tag;
	char			**command;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// loop.c
int		minishell_loop(t_shell *shell);

/*signal.c*/
void	handle_sigint(int signum);
void	setup_interactive_signals(void);
void	setup_child_signals(void);
void	setup_waitpid_signals(void);

/*clean.c*/
void	free_args(char **args);
void	free_ast(t_ast *ast);

/*utils.c*/
void	write_fd(char *cmd1, char *cmd2, char *msg, int fd);

#endif