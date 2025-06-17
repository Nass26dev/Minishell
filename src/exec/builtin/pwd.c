/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:29:03 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/17 13:40:47 by eelissal         ###   ########lyon.fr   */
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
			return (EXIT_FAILURE);
		}
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
