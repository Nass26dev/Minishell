/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:43:34 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/14 14:33:34 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


int exec_cd()
{
	
}

int	cd_get_path(t_exec *exec)
{
	//cd avec ., se deplacer la ou on est: prendre pwd (ne fait rien sauf rafraîchir certaines variables d'environnement: PWD et OLDPWD)
	//cd avec .. se deplacer dans le dossier d'au dessus (le dossier parent): prendre pwd et enlever le dernier dossier sauf s'il n'y a plus qu'un / alors ne rien faire et pas d'erreur
	//cd avec une absolute path, se deplacer dans le dossier correspondant: prendre pwd + rajouter l'absolute path + check si c'est un directory et qu'il existe
	char oldpwd[PATH_MAX];

	if (!getcwd(oldpwd, sizeof(oldpwd)))
	{
		perror("getcwd error");
		return (1);
	}
	//si . >
	//si .. >
	//si absolute
	return (0);
}

int	cd_home(t_exec *exec)
{
	char	*target;

	target = getenv("HOME");
	if (!target)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(target) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	builtin_cd(t_exec *exec)
{
	if (!exec->current->cmd)
		return (CMD_NOT_FOUND);
	else if (!exec->current->cmd->data[0])
		return (CMD_NOT_FOUND);
	else if (exec->current->cmd->data[0] && !exec->current->cmd->data[1])
		return (cd_home(exec));
	else if (exec->current->cmd->data[1] && !exec->current->cmd->data[2])
		return (cd_get_path(exec));
	else if (exec->current->cmd->data[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (1);
}
