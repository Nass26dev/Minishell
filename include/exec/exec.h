/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:36:00 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/07 18:54:08 by codespace        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

# include "minishell.h"
# include <sys/stat.h>
# include <sys/wait.h>

// # define FAIL_EXEC 126
// # define CMD_NOT_FOUND 127
// # define FAIL_FORK 128 + errno

typedef struct s_exec
{
	int				pid;
	t_ast			*root;
	t_ast			*current;
	t_shell			*shell;
	int				infd;
	int				outfd;
}	t_exec;

/*exec.c*/
int	exec_node(t_exec *exec);
int	execute(t_ast *ast, t_shell *shell);

/*exec_cmd.c*/
int	exec_cmd(t_exec *exec);

/*find_cmd_path.c*/
char	*find_cmd_path(char *cmd_name, t_vector *env);

/*exec_redir.c*/
int	exec_redir(t_exec *exec);

/*exec_pipe.c*/
int	exec_pipe(t_exec *exec);

/*exec_operator.c*/
int	exec_operator(t_exec *exec);

/*exec_parenthesis.c*/
int	exec_parenthesis(t_exec *exec);

/*exec_separator.c*/
int	exec_separator(t_exec *exec);

#endif