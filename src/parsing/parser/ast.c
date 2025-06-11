/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:59:00 by nass              #+#    #+#             */
/*   Updated: 2025/06/11 15:12:41 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_command *add_node_to_command(char *value)
{
    t_command *new;

    new = malloc(sizeof(t_command));
    if (!new)
        return (NULL);
    new->value = ft_strdup(value);
    new->next = NULL;
    return (new);
}

t_ast *create_ast_node(t_type type, char *value)
{
    t_ast *node;
    
    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->type = type;
    node->command = add_node_to_command(value);
    node->left = NULL;
    node->right = NULL;
    if (!node->command)
        return (NULL);
    return (node);
}
