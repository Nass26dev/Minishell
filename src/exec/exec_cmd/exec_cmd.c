/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:01:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/25 17:27:19 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

void	exec_extern_cmd(t_exec *exec, char *cmd)
{
	execve(cmd, exec->current->command, exec->shell->env->data);
	strerror(errno);
	// close_fds(exec); //TODO voir si utile
	free(cmd);
	free_exec(exec);
	exit(FAIL_EXEC);
}

void	is_extern_cmd(t_exec *exec, char **cmd)
{
	*cmd = find_cmd_path(exec->current->command[0], exec->shell->env);
	if (!(*cmd))
	{
		close_fds(exec); //TODO voir si utile
		printf("%s: command not found\n", exec->current->command[0]);
		free_exec(exec); //TODO to be checked
		exit (CMD_NOT_FOUND);
	}
	if (is_directory(*cmd) != 0)
	{
		close_fds(exec); //TODO voir si utile
		printf("%s: is a directory\n", exec->current->command[0]);
		free_exec(exec); //TODO to be checked
		free(*cmd);
		exit (FAIL_EXEC);
	}
}

static void	handle_child_process(t_exec *exec)
{
	char	*cmd;

	setup_child_signals();
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
	{
		ret = exec_builtin(exec, ret);
		close_fds(exec);
	}
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
		setup_waitpid_signals();
		waitpid(pid, &exec->shell->status, 0);
		ret = return_process(exec);
		setup_interactive_signals();
	}
	return (ret);
}
