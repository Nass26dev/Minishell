/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:34:07 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/18 16:31:13 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_fd(char *cmd1, char *cmd2, char *msg, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(cmd1, fd);
	if (cmd1)
		write(fd, ": ", 2);
	ft_putstr_fd(cmd2, fd);
	if (cmd2)
		write(fd, ": ", 2);
	ft_putendl_fd(msg, fd);
}
