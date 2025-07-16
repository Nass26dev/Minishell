/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:59:00 by nass              #+#    #+#             */
/*   Updated: 2025/07/16 13:32:14 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	fill_cmd_copy(char **cmd, char **copy, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		copy[i] = strdup(cmd[i]);
		if (!copy[i])
		{
			j = 0;
			while (j < i)
				free(copy[j++]);
			free(copy);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**dup_cmd(char **cmd)
{
	char	**copy;
	int		count;

	if (!cmd)
		return (NULL);
	count = 0;
	while (cmd[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	if (fill_cmd_copy(cmd, copy, count))
		return (NULL);
	copy[count] = NULL;
	return (copy);
}

bool	no_command(t_ast **n, char *value)
{
	t_ast	*node;

	node = *n;
	node->command = malloc(sizeof(char *) * 2);
	if (!node->command)
	{
		free(node);
		return (1);
	}
	node->command[0] = ft_strdup(value);
	if (!node->command[0])
	{
		free(node->command);
		free(node);
		return (1);
	}
	node->command[1] = NULL;
	return (0);
}

t_ast	*create_ast_node(t_tag tag, char *value, char **cmd)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->tag = tag;
	if (tag == CMD)
	{
		node->command = dup_cmd(cmd);
		if (!node->command)
		{
			free(node);
			return (NULL);
		}
	}
	else if (value)
	{
		if (no_command(&node, value))
			return (NULL);
	}
	else
		node->command = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
