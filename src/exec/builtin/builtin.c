/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:17:28 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/16 14:05:23 by nyousfi          ###   ########.fr       */
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
	cmd = exec->current->cmd->data[0];
	while (builtin[i])
	{
		len = ft_strlen(builtin[i]);
		if (len == ft_strlen(cmd))
		{
			if (ft_strncmp(exec->current->cmd->data[0], builtin[i], len) == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

int	exec_builtin(t_exec *exec, int builtin)
{
	int			ret;

	ret = -1;
	(void) exec;
	dup_fds(exec);
	close_fds(exec); //TODO to be checked again > maybe need -1 set up for both fds and restore fds after builtin exec
	if (builtin == CD)
		printf("exec cd\n");//ret = exec_cd(shell, exec->current->cmd->data);
	else if (builtin == ECHO)
		printf("exec echo\n");//ret = exec_echo(exec->current->cmd->data);
	else if (builtin == ENV)
		printf("exec env\n");//ret = exec_env(shell, exec);
	else if (builtin == EXIT)
		printf("exec exit\n");//ret = exec_exit(shell, exec);
	else if (builtin == EXPORT)
		printf("exec export\n");//ret = exec_export(shell, exec->current->cmd->data);
	else if (builtin == PWD)
		printf("exec pwd\n");//ret = exec_pwd(shell);
	else if (builtin == UNSET)
		printf("exec unset\n");//ret = exec_unset(shell, exec->current->cmd->data);
	return (ret);
}
