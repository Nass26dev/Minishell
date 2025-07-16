/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:09:39 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/15 19:00:33 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_node(t_exec *exec)
{
	int	ret;

	if (!exec->current)
		return (exec->shell->status);
	ret = 0;
	if (exec->current->tag == AND || exec->current->tag == OR)
		ret = exec_operator(exec);
	else if (exec->current->tag == PIPE)
		ret = exec_pipe(exec, 1);
	else if (exec->current->tag >= REDIR_IN
		&& exec->current->tag <= APPEND)
		ret = exec_redir(exec);
	else if (exec->current->tag == CMD)
		ret = exec_cmd(exec);
	return (ret);
}

static void	init_exec(t_exec *exec, t_ast *ast, t_shell *shell, t_hd *heredoc)
{
	exec->root = ast;
	exec->current = ast;
	exec->shell = shell;
	exec->infd = STDIN_FILENO;
	exec->outfd = STDOUT_FILENO;
	exec->heredoc = heredoc;
}

int	execute(t_ast *ast, t_shell *shell, t_hd *heredoc)
{
	t_exec	exec;
	int		ret;

	init_exec(&exec, ast, shell, heredoc);
	ret = exec_node(&exec);
	return (ret);
}
