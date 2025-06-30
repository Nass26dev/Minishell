/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:52:57 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/30 16:57:34 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_pipes(t_exec *exec, int pipefd[2], int pipe)
{
	close_fds(exec);
	exec->infd = STDIN_FILENO;
	exec->outfd = STDOUT_FILENO;
	if (pipe == 1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}
