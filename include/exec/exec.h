/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:36:00 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/11 14:26:56 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

# include "minishell.h"
# include <sys/stat.h>
# include <sys/wait.h>

# define FAIL_EXEC 126
# define CMD_NOT_FOUND 127
# define FAIL_FORK 128 + errno

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
void	free_exec(t_exec *exec);
int		exec_node(t_exec *exec);
int		execute(t_ast *ast, t_shell *shell);

/*exec_cmd.c*/
int		exec_cmd(t_exec *exec);
void	is_extern_cmd(t_exec *exec, char **cmd);
void	exec_extern_cmd(t_exec *exec, char *cmd);

/*exec_cmd_utils.c*/
int		cmd_is_valid(t_exec *exec);
void	dup_fds(t_exec *exec);
void	close_fds(t_exec *exec);
int		return_process(t_exec *exec);

/*find_cmd_path.c*/
char	*find_cmd_path(char *cmd_name, t_vector *env);
int		is_directory(const char *path);

/*exec_redir.c*/
int		exec_redir(t_exec *exec);

/*heredoc.c*/
int		handle_heredoc(t_exec *exec);

/*exec_pipe.c*/
int		exec_pipe(t_exec *exec);

/*exec_operator.c*/
int		exec_operator(t_exec *exec);

/*exec_parenthesis.c*/
int		exec_parenthesis(t_exec *exec);

#endif