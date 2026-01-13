/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:28:30 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 17:41:11 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_nb_args(t_token *node)
{
	t_token	*current;
	int		i;

	i = 0;
	current = node;
	while (current && !node_is_operator(current))
	{
		if (node_is_word(current))
			i++;
		current = current->next;
	}
	return (i);
}

int	fill_cmd_args(t_token **node, t_token *current, char **cmd, int *i)
{
	t_token	*prev;
	int		j;

	prev = current;
	j = 0;
	current = current->next;
	while (current && !node_is_operator(current))
	{
		if (node_is_word(current))
		{
			cmd[*i] = ft_strdup(current->value);
			if (!cmd[*i])
			{
				while (j < *i)
					free(cmd[j++]);
				free(cmd);
				return (1);
			}
			(*i)++;
			delete_node(node, current);
			current = prev;
		}
		current = current->next;
	}
	return (0);
}

int	get_cmd(t_token **node)
{
	t_token	*current;
	char	**cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(char *) * (get_nb_args(*node) + 1));
	if (!cmd)
		return (1);
	current = *node;
	cmd[i++] = ft_strdup(current->value);
	if (!cmd[i - 1])
	{
		free(cmd);
		return (1);
	}
	if (fill_cmd_args(node, current, cmd, &i))
		return (1);
	cmd[i] = NULL;
	current = *node;
	current->cmd = cmd;
	current->tag = CMD;
	return (0);
}

void	create_cmd(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (node_is_word(current))
		{
			if (get_cmd(&current))
				malloc_error(data);
		}
		current = current->next;
	}
}
