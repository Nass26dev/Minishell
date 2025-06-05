/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:58:13 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/05 12:05:34 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
#define MINISHELL_EXEC_H

# include <minishell.h>

typedef struct s_exec
{
	int				pid;
	t_ast			*root;
	t_ast			*current;
	t_shell			*shell;
	int				infd;
	int				outfd;
}	t_exec;

typedef enum e_builtin
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET,
}	t_builtin;

#endif