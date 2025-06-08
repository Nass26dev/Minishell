/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:09:39 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/07 21:05:30 by codespace        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

int	exec_node(t_exec *exec)
{
	int	ret;

	if (!exec->current)
		return (0);
	ret = 0;
	if (exec->current->tag == AST_PARENTHESIS)
		ret = exec_parenthesis(exec);
	else if (exec->current->tag == AST_AND || exec->current->tag == AST_OR)
		ret = exec_operator(exec);
	else if (exec->current->tag == AST_PIPE)
		ret = exec_pipe(exec);
	else if (exec->current->tag >= AST_REDIR_IN
		&& exec->current->tag <= AST_APPEND)
		ret = exec_redir(exec);
	else if (exec->current->tag == AST_CMD)
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
	if (exec.root->tag == AST_CMD)
	{
		ret = is_builtin(&exec);
		if (ret >= 0 && ret < 7)
			ret = exec_builtin(&exec, ret, shell);
		else
			ret = exec_cmd(&exec);
	}
	else
		ret = exec_node(&exec);
	return (ret);
}
