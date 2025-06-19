/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:30:55 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/19 13:23:01 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
#define BUILTIN_H

# include "exec.h"

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

/*builtin.c*/
int	is_builtin(t_exec *exec);
int	exec_builtin(t_exec *exec, int ret);

/*env.c*/
int	builtin_env(t_exec *exec);

/*echo.c*/
int	builtin_echo(char **data);

/*cd.c*/
int	builtin_cd(t_exec *exec);

/*pwd.c*/
int	builtin_pwd(t_exec *exec);

/*export.c*/
int	builtin_export(t_shell *shell, char **data);
int	add_env_var(t_vector *env, char *name, char *value);

/*unset.c*/
int	builtin_unset(t_exec *exec);
int	find_env_var_index(t_vector *env, char *var);

/*exit.c*/
int	builtin_exit(t_exec *exec);

#endif