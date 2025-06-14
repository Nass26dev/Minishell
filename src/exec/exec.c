/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:09:39 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/14 13:46:31 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

void	free_exec(t_exec *exec)
{
	if (exec->shell)
		free_shell(exec->shell);
	if (exec->root)
		free_ast(exec->root);
}

int	exec_node(t_exec *exec)
{
	int	ret;

	if (!exec->current)
		return (0);
	ret = 0;
	if (exec->current->tag == PARENTHESIS)
		ret = exec_parenthesis(exec);
	else if (exec->current->tag == AND || exec->current->tag == OR)
		ret = exec_operator(exec);
	else if (exec->current->tag == PIPE)
		ret = exec_pipe(exec);
	else if (exec->current->tag >= REDIR_IN
		&& exec->current->tag <= APPEND)
		ret = exec_redir(exec);
	else if (exec->current->tag == CMD)
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
}

int	execute(t_ast *ast, t_shell *shell)
{
	t_exec	exec;
	int		ret;

	init_exec(&exec, ast, shell);
	ret = exec_node(&exec);
	// shell = &exec.shell;
	return (ret);
}
