/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:36:00 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/05 17:07:12 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

# include "minishell.h"

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

/*exec_redir.c*/
int	exec_redir(t_exec *exec);

/*exec_pipe.c*/
int	exec_pipe(t_exec *exec);

/*exec_operator.c*/
int	exec_operator(t_exec *exec);

#endif