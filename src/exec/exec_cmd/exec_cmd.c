/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:01:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/06 16:21:21 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	exec_cmd(t_exec *exec)
{
	if (!exec->current->cmd || !exec->current->cmd->data
		|| !exec->current->cmd->data[0] || !exec->current->cmd->data[0][0])
	{
		// close_fds(exec);
		printf("command not found\n");
		return (127);
	}
	//exec cmd
	return (0);
}
