/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:45:35 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/29 22:09:22 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	dup_pipe_fds(t_exec *exec, int infd, int outfd, int fd)
{
	if (fd == 0)
	{
		if (dup2(outfd, STDOUT_FILENO) == -1)
			handle_dup_error(exec, NULL, infd, outfd);
		close (outfd);
		if (infd > 2)
		{
			if (dup2(infd, STDIN_FILENO) == -1)
				handle_dup_error(exec, NULL, infd, outfd);
			close(infd);
		}
	}
	else
	{
		if (dup2(infd, STDIN_FILENO) == -1)
			handle_dup_error(exec, NULL, infd, outfd);
		close (infd);
		if (outfd > 2)
		{
			if (dup2(outfd, STDOUT_FILENO) == -1)
				handle_dup_error(exec, NULL, infd, outfd);
			close(outfd);
		}
	}
}

static void	redirect_fds_left(t_exec *exec, int fd[2], int *infd, int *outfd)
{
	*infd = exec->infd;
	if (exec->outfd > 2)
	{
		*outfd = exec->outfd;
		close(fd[1]);
	}
	else
		*outfd = fd[1];
	close(fd[0]);
}

static void	redirect_fds_right(t_exec *exec, int fd[2], int *infd, int *outfd)
{
	*outfd = exec->outfd;
	if (exec->infd > 2)
	{
		*infd = exec->infd;
		close(fd[0]);
	}
	else
		*infd = fd[0];
	close(fd[1]);
}

void	handle_redirections(t_exec *exec, int pipefd[2], int side)
{
	int		infd;
	int		outfd;

	if (side == 0)
		redirect_fds_left (exec, pipefd, &infd,&outfd);
	else
		redirect_fds_right(exec, pipefd, &infd,&outfd);
	dup_pipe_fds(exec, infd, outfd, side);
	if (side == 0 && exec->outfd > 2)
		exec->outfd = STDOUT_FILENO;
	else if (side == 1 && exec->infd > 2)
		exec->infd = STDIN_FILENO;
}

t_exec	*exec_redir_pipe(t_exec *exec)
{
	if (exec->current->tag == REDIR_OUT)
		exec->shell->status = handle_redir_out(exec);
	else if (exec->current->tag == APPEND)
		exec->shell->status = handle_append(exec);
	else if (exec->current->tag == REDIR_IN)
		exec->shell->status = handle_redir_in(exec);
	else if (exec->current->tag == HEREDOC)
		exec->shell->status = handle_heredoc(exec);
	exec->current = exec->current->left;
	return (exec);
}
