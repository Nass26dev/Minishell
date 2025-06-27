/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:59:00 by nass              #+#    #+#             */
/*   Updated: 2025/06/27 16:19:18 by nyousfi          ###   ########.fr       */
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
	if (tag == TOKEN_CMD)
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

// void	print_indent(int depth)
// {
// 	for (int i = 0; i < depth; i++)
// 		printf(" ");
// }

// void	print_node(t_ast *node)
// {
// 	if (!node)
// 	{
// 		printf("(null)\n");
// 		return ;
// 	}
// 	if (node->tag == TOKEN_AND)
// 		printf("AND\n");
// 	else if (node->tag == TOKEN_OR)
// 		printf("OR\n");
// 	else if (node->tag == TOKEN_PIPE)
// 		printf("PIPE\n");
// 	else if (node->tag == TOKEN_CMD)
// 	{
// 		printf("CMD:");
// 		if (node->command[0])
// 		{
// 			for (int i = 0; node->command[i]; i++)
// 				printf(" | %s", node->command[i]);
// 			printf("\n");
// 		}
// 		else
// 			printf(" (null)\n");
// 	}
// 	else if (node->tag == TOKEN_REDIR_IN)
// 		printf("REDIR IN: %s\n",
// 			node->command[0] ? node->command[0] : "(null)");
// 	else if (node->tag == TOKEN_REDIR_OUT)
// 		printf("REDIR OUT: %s\n",
// 			node->command[0] ? node->command[0] : "(null)");
// 	else if (node->tag == TOKEN_APPEND)
// 		printf("APPEND: %s\n", node->command[0] ? node->command[0] : "(null)");
// 	else if (node->tag == TOKEN_HEREDOC)
// 		printf("HEREDOC: %s\n", node->command[0] ? node->command[0] : "(null)");
// 	else
// 		printf("UNKNOWN (%d)\n", node->tag);
// }

// #define INDENT_STEP 4

// void	print_ast(t_ast *node, int depth)
// {
// 	if (!node)
// 		return ;
// 	if (depth == 0)
// 		printf("vers le haut = droite , vers le bas = gauche\n");
// 	if (node->right)
// 		print_ast(node->right, depth + INDENT_STEP);
// 	print_indent(depth);
// 	print_node(node);
// 	if (node->left)
// 		print_ast(node->left, depth + INDENT_STEP);
// }
