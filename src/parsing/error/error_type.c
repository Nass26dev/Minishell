/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:11:01 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 14:11:47 by nyousfi          ###   ########.fr       */
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
	printf("syntax error near unexpected token « ");
	if (tag == TOKEN_AND)
		printf("&& »\n");
	if (tag == TOKEN_APPEND)
		printf(">> »\n");
	if (tag == TOKEN_HEREDOC)
		printf("<< »\n");
	if (tag == TOKEN_OR)
		printf("|| »\n");
	if (tag == TOKEN_PIPE)
		printf("| »\n");
	if (tag == TOKEN_REDIR_IN)
		printf("< »\n");
	if (tag == TOKEN_REDIR_OUT)
		printf("> »\n");
}
