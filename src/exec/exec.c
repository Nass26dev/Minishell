/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:09:39 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/27 14:13:44 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_node(t_exec *exec)
{
	int	ret;

	if (!exec->current)
		return (0);
	ret = 0;
	if (exec->current->tag == TOKEN_PARENTHESIS)
		ret = exec_parenthesis(exec);
	else if (exec->current->tag == TOKEN_AND || exec->current->tag == TOKEN_OR)
		ret = exec_operator(exec);
	else if (exec->current->tag == TOKEN_PIPE)
		ret = exec_pipe(exec);
	else if (exec->current->tag >= TOKEN_REDIR_IN
		&& exec->current->tag <= TOKEN_APPEND)
		ret = exec_redir(exec);
	else if (exec->current->tag == TOKEN_CMD)
		ret = exec_cmd(exec);
	return (ret);
}

static void	init_exec(t_exec *exec, t_ast *ast, t_shell *shell)
{
	exec->root = ast;
	exec->current = ast;
	exec->shell = shell;
	exec->infd = STDIN_FILENO;
	exec->outfd = STDOUT_FILENO;
	exec->heredoc  = NULL;
}

int	execute(t_ast *ast, t_shell *shell)
{
	t_exec	exec;
	int		ret;

	init_exec(&exec, ast, shell);
	ret = exec_node(&exec);
	return (ret);
}
