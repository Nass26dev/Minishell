/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:53:44 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 16:36:15 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif

# include "env.h"
# include "libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BLUE
#  define BLUE "\033[1;34m"
# endif
# ifndef PURPLE
#  define PURPLE "\033[1;35m"
# endif
# ifndef RESET
#  define RESET "\033[0m"
# endif

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
}					t_tag;

extern int			received_signal;

typedef struct s_ast
{
	t_tag			tag;
	char			**command;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

// loop.c
int					minishell_loop(t_shell *shell);

/*signal.c*/
void				handle_sigint(int signum);
void				setup_interactive_signals(void);
void				setup_child_signals(void);
void				setup_waitpid_signals(void);

/*clean.c*/
void				free_args(char **args);
void				free_ast(t_ast *ast);

/*utils.c*/
void				write_fd(char *cmd1, char *cmd2, char *msg, int fd);
char				*free_strjoin(char *s1, char *s2);
char				*set_empty(void);

#endif