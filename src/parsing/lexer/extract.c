/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:56:26 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 17:41:11 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_final_segment(char *content, t_token **head, int start, int end)
{
	char	*last;

	last = ft_substr(content, start, end - start);
	if (last)
	{
		add_token(head, create_token(last, WORD));
		free(last);
	}
}

void	handle_dollar_case(char *content, t_token **head, int *start, int *i)
{
	char	*before;
	char	*dollar;

	if (*i > *start)
	{
		before = ft_substr(content, *start, *i - *start);
		if (before)
		{
			add_token(head, create_token(before, WORD));
			free(before);
		}
	}
	dollar = ft_substr(content, *i, 1);
	if (dollar)
	{
		add_token(head, create_token(dollar, WORD));
		free(dollar);
	}
	(*i)++;
	*start = *i;
}

t_token	*split_tokens(char *content)
{
	t_token	*head;
	int		i;
	int		start;

	head = NULL;
	i = 0;
	start = 0;
	while (content[i])
	{
		if (content[i] == '$' && (content[i + 1] == '\0' || ft_isspace(content[i
						+ 1]) || content[i + 1] == '$'))
		{
			handle_dollar_case(content, &head, &start, &i);
			continue ;
		}
		i++;
	}
	if (i > start)
		handle_final_segment(content, &head, start, i);
	return (head);
}
