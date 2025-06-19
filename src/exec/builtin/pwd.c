/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:29:03 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/18 11:39:34 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(t_exec *exec)
{
	char	*pwd;

	pwd = get_env(exec->shell->env, "PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			printf("pwd: error retrieving current directory\n");
			return (1);
		}
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
