/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:30:55 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/17 15:35:35 by eelissal         ###   ########lyon.fr   */
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

/*unset.c*/
int	builtin_unset(t_exec *exec);
int	find_var_index_in_env(t_vector *env, char *var);

#endif