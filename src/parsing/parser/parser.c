/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:04:43 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/11 15:12:24 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int get_operator_priority(t_type type)
{
    if (type == TOKEN_OR)
        return (1);
    if (type == TOKEN_AND)
        return (2);
    if (type == TOKEN_PIPE)
        return (3);
    return (100); // for words/commands
}

t_token *find_main_operator(t_token *start, t_token *end)
{
    t_token *current;
    t_token *main_op;
    int min_prio;
    int priority;

    current = start;
    main_op = NULL;
    min_prio = 100;

    while (current && current != end)
    {
        priority = get_operator_priority(current->tag);
        if (priority < min_prio)
        {
            min_prio = priority;
            main_op = current;
        }
        current = current->next;
    }
    return (main_op);
}

t_ast *parser(t_data *data, t_token *start, t_token *end)
{
    t_token *main_op;
    t_ast *node;

	main_op = find_main_operator(start, end);
    if (main_op)
    {
        node = create_ast_node(main_op->tag, NULL);
        node->left = parser(data, start, main_op);
        node->right = parser(data, main_op->next, end);
        return (node);
    }
    // si il n'y a pas d'operateur , c'est un mot ou une commande simple
    if (start && start != end && (start->tag == TOKEN_WORD
        || start->tag == TOKEN_DOUBLE_QUOTE || start->tag == TOKEN_SINGLE_QUOTE))
        return (create_ast_node(start->tag, start->value));
    return (NULL);
}
