/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:01:04 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/07 20:05:58 by codespace        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_directory(const char *path)
{
	struct stat	buffer;

	if (stat(path, &buffer) != 0)
		return (0);
	return (S_ISDIR(buffer.st_mode));
}

void	close_fds(t_exec *exec)
{
	if (exec->infd != STDIN_FILENO)
		close(exec->infd);
	if (exec->outfd != STDOUT_FILENO)
		close(exec->outfd);
}

static void	handle_child_process(t_exec *exec, char *cmd)
{
	if (exec->infd != STDIN_FILENO)
	{
		dup2(exec->infd, STDIN_FILENO);
		close(exec->infd);
	}
	if (exec->outfd != STDOUT_FILENO)
	{
		dup2(exec->outfd, STDOUT_FILENO);
		close(exec->outfd);
	}
	execve(cmd, exec->current->cmd->data, exec->shell->env->data);
	strerror(errno);
	free(cmd);
	free_shell(exec->shell);
	if (exec->root)
		free_ast(exec->root);
	exit(FAIL_EXEC);
}

static int	handle_parent_process(t_exec *exec, pid_t pid)
{
	close_fds(exec);
	exec->infd = STDIN_FILENO;
	exec->outfd = STDOUT_FILENO;
	waitpid(pid, &exec->shell->status, 0);
	if (WIFEXITED(exec->shell->status))
		return (WEXITSTATUS(exec->shell->status));
	else if (WIFSIGNALED(exec->shell->status))
		return (128 + WTERMSIG(exec->shell->status));
	return (exec->shell->status);
}

int	exec_cmd(t_exec *exec)
{
	int		ret;
	char	*cmd;
	pid_t	pid;

	if (!exec->current->cmd || !exec->current->cmd->data
		|| !exec->current->cmd->data[0] || !exec->current->cmd->data[0][0])
	{
		close_fds(exec);
		printf("command not found\n");
		return (CMD_NOT_FOUND);
	}
	cmd = find_cmd_path(exec->current->cmd->data[0], exec->shell->env);
	if (!cmd)
	{
		close_fds(exec);
		printf("%s: command not found\n", exec->current->cmd->data[0]);
		return (CMD_NOT_FOUND);
	}
	if (is_directory(cmd) != 0)
	{
		strerror(errno); // printf("%s: is a directory\n", exec->current->cmd->data[0]);
		free(cmd);
		//close_fds(exec); ???
		return (FAIL_EXEC);
	}
	pid = fork();
	if (pid == -1)
		return (FAIL_FORK);
	if (pid == 0)
		handle_child_process(exec, cmd);
	ret = handle_parent_process(exec, pid);
	free(cmd);	
	return (ret);
}
