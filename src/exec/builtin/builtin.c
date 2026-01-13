/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:17:28 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/14 17:47:17 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

int	is_builtin(t_exec *exec)
{
	static char	*builtin[] = {"cd", "echo", "env", "exit", "export",
		"pwd", "unset", NULL};
	int			i;
	size_t		len;
	char		*cmd;

	i = 0;
	cmd = exec->current->command[0];
	while (builtin[i])
	{
		len = ft_strlen(builtin[i]);
		if (len == ft_strlen(cmd))
		{
			if (ft_strncmp(cmd, builtin[i], len) == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

int	exec_builtin(t_exec *exec, int builtin)
{
	int	ret;

	ret = -1;
	if (builtin == CD)
		ret = builtin_cd(exec);
	else if (builtin == ECHO)
		ret = builtin_echo(exec->current->command, STDOUT_FILENO);
	else if (builtin == ENV)
		ret = builtin_env(exec, 0);
	else if (builtin == EXIT)
		ret = builtin_exit(exec);
	else if (builtin == EXPORT)
		ret = builtin_export(exec);
	else if (builtin == PWD)
		ret = builtin_pwd(exec);
	else if (builtin == UNSET)
		ret = builtin_unset(exec);
	return (ret);
}
