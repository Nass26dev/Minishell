/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:59:00 by nass              #+#    #+#             */
/*   Updated: 2025/06/16 11:08:23 by nyousfi          ###   ########.fr       */
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
        node->command = ft_strdup(value);
        if (!node->command)
        return (NULL);
    }
    else
        node->command = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
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
		printf("CMD: %s\n", node->command ? node->command : "(null)");
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
