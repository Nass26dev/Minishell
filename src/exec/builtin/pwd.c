/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:29:03 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/23 13:53:15 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(t_exec *exec)
{
	char	*pwd;
	int		len;

	pwd = get_env(exec->shell->env, "PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			write(2, "pwd: error retrieving current directory\n", 39);
			return (1);
		}
	}
	len = ft_strlen(pwd);
	write(exec->outfd, pwd, len);
	write(exec->outfd, "\n", 1);
	free(pwd);
	return (0);
}
