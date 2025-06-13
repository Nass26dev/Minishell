/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:30:55 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/13 15:27:54 by eelissal         ###   ########lyon.fr   */
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
int	exec_env(t_exec *exec);

/*echo.c*/
int	exec_echo(char **data);

#endif