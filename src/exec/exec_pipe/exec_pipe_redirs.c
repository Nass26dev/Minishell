/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:45:35 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/22 16:59:30 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	dup_pipe_fds(int infd, int outfd, int fd)
{
	if (fd == 0)
	{
		dup2(outfd, STDOUT_FILENO);
		close (outfd);
		if (infd != STDIN_FILENO)
		{
			dup2(infd, STDIN_FILENO);
			close(infd);
		}
	}
	else
	{
		dup2(infd, STDIN_FILENO);
		close (infd);
		if (outfd != STDOUT_FILENO)
		{
			dup2(outfd, STDOUT_FILENO);
			close(outfd);
		}
	}
}

static void	redirect_fds_left(t_exec *exec, int fd[2], int *infd, int *outfd)
{
	*infd = exec->infd;
	if (exec->outfd != STDOUT_FILENO)
		*outfd = exec->outfd;
	else
		*outfd = fd[1];
	close(fd[0]);
}

static void	redirect_fds_right(t_exec *exec, int fd[2], int *infd, int *outfd)
{
	if (exec->infd != STDIN_FILENO)
		*infd = exec->infd;
	else
		*infd = fd[0];
	*outfd = exec->outfd;
	close(fd[1]);
}

void	handle_redirections(t_exec *exec, int pipefd[2], int fd)
{
	int		infd;
	int		outfd;

	if (fd == 0)
		redirect_fds_left(exec, pipefd, &infd, &outfd);
	else
		redirect_fds_right(exec, pipefd, &infd, &outfd);
	dup_pipe_fds(infd, outfd, fd);
}

t_exec	*exec_redir_pipe(t_exec *exec)
{
	if (exec->current->tag == TOKEN_REDIR_IN)
		exec->shell->status = handle_redir_in(exec);
	else if (exec->current->tag == TOKEN_HEREDOC)
		exec->shell->status = handle_heredoc(exec);
	else if (exec->current->tag == TOKEN_REDIR_OUT)
		exec->shell->status = handle_redir_out(exec);
	else if (exec->current->tag == TOKEN_APPEND)
		exec->shell->status = handle_append(exec);
	exec->current = exec->current->left;
	return (exec);
}
