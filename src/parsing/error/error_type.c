/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:11:01 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/15 19:05:27 by eelissal         ###   ########lyon.fr   */
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
	free_all_heredocs(&data->heredoc);
	ft_putstr_fd("malloc error\n", STDERR_FILENO);
	free_tokens(&data->tokens);
	free_shell(data->shell);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	print_correct_error(t_tag tag, t_data *data)
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
	data->shell->status = 2;
}

bool	check_redir_error(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (char_is_redir(input[i]) && char_is_redir(input[i + 1]))
			i++;
		if (char_is_redir(input[i]) && input[i + 1] && input[i + 1] == ' '
			&& input[i + 2] && is_operator(input[i + 2]))
		{
			print_correct_error(find_correct_tag(input[i]), data);
			return (true);
		}
		if (input[i] == '"')
		{
			i++;
			while (input[i] != '"' && input[i])
				i++;
		}
		if (else_case(input, &i, data))
			return (true);
		i++;
	}
	return (false);
}
