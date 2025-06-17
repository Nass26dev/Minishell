/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:34:07 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/17 15:34:27 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_fd(char *cmd, char *msg, int fd)
{
	ft_putstr_fd("minishell:", fd);
	ft_putstr_fd(cmd, fd);
	write(fd, ": ", 2);
	ft_putendl_fd(msg, fd);
}
