/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:59:00 by nass              #+#    #+#             */
/*   Updated: 2025/06/19 14:23:31 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast *create_ast_node(t_type type, char *value)
{
    t_ast *node;
    
    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->type = type;
    if (value)
    {
        node->command[0] = ft_strdup(value);
		node->command[1] = NULL;
		node->command[2] = NULL;
        if (!node->command[0])
        	return (NULL);
    }
    else
        node->command[0] = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

void add_args_to_command(t_ast **node, char *args)
{
	t_ast *tmp;

	tmp = *node;
	tmp->command[1] = ft_strdup(args);
}

void print_indent(int depth)
{
	for (int i = 0; i < depth; i++)
		printf(" ");
}

void print_node(t_ast *node)
{
	if (!node)
	{
		printf("(null)\n");
		return;
	}

	if (node->type == TOKEN_AND)
		printf("AND\n");
	else if (node->type == TOKEN_OR)
		printf("OR\n");
	else if (node->type == TOKEN_PIPE)
		printf("PIPE\n");
	else if (node->type == TOKEN_WORD || node->type == TOKEN_DOUBLE_QUOTE || node->type == TOKEN_SINGLE_QUOTE)
	{
		printf("CMD:");
		if (node->command[0])
		{
			for (int i = 0; node->command[i]; i++)
			{
				if (i == 1)
					printf(" ,");	
				printf(" %s", node->command[i]);
			}
			printf("\n");
		}
		else
			printf(" (null)\n");
	}
	else if (node->type == TOKEN_REDIR_IN)
		printf("REDIR IN: %s\n", node->command[0] ? node->command[0] : "(null)");
	else if (node->type == TOKEN_REDIR_OUT)
		printf("REDIR OUT: %s\n", node->command[0] ? node->command[0] : "(null)");
	else if (node->type == TOKEN_APPEND)
		printf("APPEND: %s\n", node->command[0] ? node->command[0] : "(null)");
	else if (node->type == TOKEN_HEREDOC)
		printf("HEREDOC: %s\n", node->command[0] ? node->command[0] : "(null)");
	else
		printf("UNKNOWN (%d)\n", node->type);
}

#define INDENT_STEP 4

void print_ast(t_ast *node, int depth)
{
	if (!node)
		return;
	if (depth == 0)
    	printf("vers le haut = droite , vers le bas = gauche\n");
	// D’abord le sous-arbre droit (en haut)
	if (node->right)
		print_ast(node->right, depth + INDENT_STEP);

	// Affiche le nœud courant
	print_indent(depth);
	print_node(node);

	// Puis le sous-arbre gauche (en bas)
	if (node->left)
		print_ast(node->left, depth + INDENT_STEP);
}
