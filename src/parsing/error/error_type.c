/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:11:01 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/30 12:07:59 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	syntax_error(t_data *data, char *error)
{
	free_tokens(&data->tokens);
	ft_putstr_fd(error, STDERR_FILENO);
	data->error = true;
}

void	malloc_error(t_data *data)
{
	ft_putstr_fd("malloc error\n", STDERR_FILENO);
	free_tokens(&data->tokens);
	free_shell(data->shell);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	print_correct_error(t_tag tag)
{
	ft_putstr_fd("syntax error near unexpected token « ", STDERR_FILENO);
	if (tag == AND)
		ft_putstr_fd("&& »\n", STDERR_FILENO);
	if (tag == APPEND)
		ft_putstr_fd(">> »\n", STDERR_FILENO);
	if (tag == HEREDOC)
		ft_putstr_fd("<< »\n", STDERR_FILENO);
	if (tag == OR)
		ft_putstr_fd("|| »\n", STDERR_FILENO);
	if (tag == PIPE)
		ft_putstr_fd("| »\n", STDERR_FILENO);
	if (tag == REDIR_IN)
		ft_putstr_fd("< »\n", STDERR_FILENO);
	if (tag == REDIR_OUT)
		ft_putstr_fd("> »\n", STDERR_FILENO);
	if (tag == 13)
	ft_putstr_fd("& »\n", STDERR_FILENO);		
}
