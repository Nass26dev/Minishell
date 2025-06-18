/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:43:34 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/18 16:37:57 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*ft_strcut(const char *s, size_t start)
{
	size_t	len;
	char	*new;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (start > len)
		start = len;
	new = malloc(sizeof(char) * (start + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, s, start);
	new[start] = '\0';
	return (new);
}

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
	if (access(newpwd, F_OK | X_OK) != 0)
	{
		printf("cd: %s: %s\n", newpwd, strerror(errno));
		return (1);
	}
	if (is_directory(newpwd) == 0)
	{
		printf("cd: %s: %s\n", newpwd, strerror(ENOTDIR));
		return (1);
	}
	if (chdir(newpwd) != 0)
	{
		perror("cd: chdir fail");
		return (1);
	}
	return (add_env_var(env, "PWD", newpwd));
}
// else
// {
// 	set_env("OLDPWD", oldpwd);
// 	char *currpwd = getcwd(NULL, 0);
// 	set_env("PWD", currpwd);
// 	free(currpwd);
// }

int	cd_get_path(char *target, t_vector *env)
{
	char		oldpwd[PATH_MAX];
	char		*newpwd;

	if (!getcwd(oldpwd, sizeof(oldpwd)))
	{
		perror("getcwd error");
		return (1);
	}
	if (ft_strcmp(target, ".") == 0) //TODO fix if ./././
		newpwd = ft_strdup(oldpwd);
	else if (ft_strcmp(target, "..") == 0) //TODO fix if ../../..
		newpwd = ft_strdup(ft_strrchr(oldpwd, '/'));
	else
		newpwd = ft_strjoin(oldpwd, target);
	if (!newpwd)
		return (1);
	if (exec_cd(newpwd, env) != 0)
	{
		free(newpwd);
		return (1);
	}
	return (add_env_var(env, "OLDPWD", oldpwd));
}

int	cd_home(char *target, t_vector *env)
{
	char		oldpwd[PATH_MAX];
	char		*newpwd;

	if (!getcwd(oldpwd, sizeof(oldpwd)))
	{
		perror("getcwd error");
		return (1);
	}
	newpwd = getenv(target);
	if (!newpwd)
	{
		printf("cd: %s not set\n", target);
		return (1);
	}
	if (exec_cd(newpwd, env) != 0)
	{
		free(newpwd);
		return (1);
	}
	return (add_env_var(env, "OLDPWD", oldpwd));
}

int	builtin_cd(t_exec *exec)
{
	if (exec->current->cmd->data[0] && !exec->current->cmd->data[1])
		return (cd_home("HOME", exec->shell->env));
	else if (exec->current->cmd->data[1] && !exec->current->cmd->data[2])
		return (cd_get_path(exec->current->cmd->data[1], exec->shell->env));
	else
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
}
