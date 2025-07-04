/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:01:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/04 12:52:27 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

void	exec_extern_cmd(t_exec *exec, char *cmd)
{
	execve(cmd, exec->current->command, exec->shell->env->data);
	write_fd(cmd, NULL, strerror(errno), 2);
	free(cmd);
	free_exec(exec);
	exit(FAIL_EXEC);
}

void	is_extern_cmd(t_exec *exec, char **cmd)
{
	*cmd = find_cmd_path(exec->current->command[0], exec->shell->env);
	if (!(*cmd))
	{
		close_fds(exec);
		write_fd(exec->current->command[0], NULL, "command not found", 2);
		free_exec(exec);
		exit (CMD_NOT_FOUND);
	}
	if (is_directory(*cmd) != 0)
	{
		close_fds(exec);
		write_fd(exec->current->command[0], NULL, "is a directory", 2);
		free_exec(exec);
		free(*cmd);
		exit (FAIL_EXEC);
	}
}

static void	handle_child_process(t_exec *exec)
{
	char	*cmd;

	setup_child_signals();
	is_extern_cmd(exec, &cmd);
	dup_fds(exec, cmd);
	exec_extern_cmd(exec, cmd);
}

static int	waitpid_process(t_exec	*exec, pid_t pid)
{
	int	ret;

	setup_waitpid_signals();
	waitpid(pid, &exec->shell->status, 0);
	ret = return_process(exec->shell->status, 1);
	exec->shell->status = ret;
	setup_interactive_signals();
	return (ret);
}

int	exec_cmd(t_exec *exec)
{
	pid_t	pid;
	int		ret;

	exec->shell->status = cmd_is_valid(exec);
	if (exec->shell->status != 0)
		return (exec->shell->status);
	ret = is_builtin(exec);
	if (ret >= 0 && ret < 7)
	{
		ret = exec_builtin(exec, ret);
		close_fds(exec);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (handle_fork_error(exec, NULL, errno, 0));
		if (pid == 0)
			handle_child_process(exec);
		close_fds(exec);
		ret = waitpid_process(exec, pid);
	}
	exec->shell->status = ret;
	return (exec->shell->status);
}
