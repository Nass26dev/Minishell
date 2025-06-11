/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:01:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/10 18:37:34 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

static int	waitpid_process(t_exec *exec, int pid)
{
	waitpid(pid, &exec->shell->status, 0);
	if (WIFEXITED(exec->shell->status))
		return (WEXITSTATUS(exec->shell->status));
	else if (WIFSIGNALED(exec->shell->status))
		return (128 + WTERMSIG(exec->shell->status));
	return (exec->shell->status);
}

void	exec_extern_cmd(t_exec *exec, char *cmd)
{
	execve(cmd, exec->current->cmd->data, exec->shell->env->data);
	strerror(errno);
	// close_fds(exec); //TODO voir si utile
	free(cmd);
	if (exec->root)
		free_ast(exec->root);
	if (exec->shell)
		free_shell(exec->shell);
	exit(FAIL_EXEC);
}

void	is_extern_cmd(t_exec *exec, char **cmd)
{
	*cmd = find_cmd_path(exec->current->cmd->data[0], exec->shell->env);
	if (!(*cmd))
	{
		close_fds(exec); //TODO voir si utile
		printf("%s: command not found\n", exec->current->cmd->data[0]);
		free_exec(exec); //TODO to be checked
		exit (CMD_NOT_FOUND);
	}
	if (is_directory(*cmd) != 0)
	{
		close_fds(exec); //TODO voir si utile
		printf("%s: is a directory\n", exec->current->cmd->data[0]);
		free_exec(exec); //TODO to be checked
		free(*cmd);
		exit (FAIL_EXEC);
	}
}

static void	handle_child_process(t_exec *exec)
{
	char	*cmd;

	is_extern_cmd(exec, &cmd);
	dup_fds(exec);
	exec_extern_cmd(exec, cmd);
}

int	exec_cmd(t_exec *exec)
{
	pid_t	pid;
	int		ret;

	ret = cmd_is_valid(exec);
	if (ret != 0)
		return (ret);
	ret = is_builtin(exec);
	if (ret >= 0 && ret < 7)
		ret = exec_builtin(exec, ret);
	else
	{
		pid = fork();
		if (pid == -1)
			return (FAIL_FORK);
		if (pid == 0)
			handle_child_process(exec);
		close_fds(exec);
		exec->infd = STDIN_FILENO;
		exec->outfd = STDOUT_FILENO;
		ret = waitpid_process(exec, pid);
	}
	return (ret);
}
