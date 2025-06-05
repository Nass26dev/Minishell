/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:36:00 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/05 16:30:21 by eelissal         ###   ########lyon.fr   */
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
int	exec_command(t_exec *exec);

#endif