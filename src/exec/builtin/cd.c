/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:43:34 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/27 16:35:06 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
- cd avec ., se deplacer la ou on est: prendre pwd (ne fait rien sauf rafraîchir
certaines variables d'environnement: PWD et OLDPWD)
- cd avec .. se deplacer dans le dossier d'au dessus (le dossier parent): prendre
pwd et enlever le dernier dossier sauf s'il n'y a plus qu'un / alors ne rien
faire et pas d'erreur
- cd avec une absolute path, se deplacer dans le dossier correspondant: prendre
pwd + rajouter l'absolute path + check si c'est un directory et qu'il existe
*/
int	exec_cd(char *newpwd, t_vector *env)
{
	int	ret;

	if (access(newpwd, F_OK | X_OK) != 0)
	{
		write_fd("cd", newpwd, strerror(errno), 2);
		return (1);
	}
	if (is_directory(newpwd) == 0)
	{
		write_fd("cd", newpwd, strerror(ENOTDIR), 2);
		return (1);
	}
	if (chdir(newpwd) != 0)
	{
		perror("cd: chdir fail");
		return (1);
	}
	ret = add_env_var(env, "PWD", newpwd);
	if (ret != 0)
		write_fd("cd", "PWD", "not exported", 2);
	return (ret);
}

int	update_pwd(t_vector *env, char oldpwd[PATH_MAX], char newpwd[PATH_MAX])
{
	int	ret;

	ret = add_env_var(env, "PWD", newpwd);
	if (ret != 0)
		write_fd("cd", "PWD", "not exported", 2);
	ret = add_env_var(env, "OLDPWD", oldpwd);
	if (ret != 0)
		write_fd("cd", "PWD", "not exported", 2);
	return (ret);
}

int	cd_get_path(char *target, t_vector *env)
{
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];

	if (!getcwd(oldpwd, sizeof(oldpwd)))
	{
		perror("getcwd error");
		return (1);
	}
	if (chdir(target) != 0)
	{
		write_fd("cd", target, strerror(errno), 2);
		return (1);
	}
	if (!getcwd(newpwd, sizeof(newpwd)))
	{
		perror("getcwd error");
		chdir(oldpwd);
		return (1);
	}
	return (update_pwd(env, oldpwd, newpwd));
}

int	cd_home(char *target, t_vector *env)
{
	char	oldpwd[PATH_MAX];
	char	*newpwd;
	int		ret;

	if (!getcwd(oldpwd, sizeof(oldpwd)))
	{
		perror("getcwd error");
		return (1);
	}
	newpwd = getenv(target);
	if (!newpwd)
	{
		write_fd("cd", target, "not set", 2);
		return (1);
	}
	if (exec_cd(newpwd, env) != 0)
	{
		free(newpwd);
		return (1);
	}
	ret = add_env_var(env, "OLDPWD", oldpwd);
	if (ret != 0)
		write_fd("cd", "PWD", "not exported", 2);
	return (ret);
}

int	builtin_cd(t_exec *exec)
{
	if (exec->current->command[0] && !exec->current->command[1])
		return (cd_home("HOME", exec->shell->env));
	else if (exec->current->command[1] && !exec->current->command[2])
		return (cd_get_path(exec->current->command[1], exec->shell->env));
	else
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
}
