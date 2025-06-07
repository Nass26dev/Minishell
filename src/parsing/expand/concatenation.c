/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:12:06 by nass              #+#    #+#             */
/*   Updated: 2025/06/07 12:44:25 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool should_concatenate(t_token *current, t_token *next)
{
    if (!current || !next)
        return (false);
    if (next->tag != TOKEN_WORD && next->tag != TOKEN_DOUBLE_QUOTE && next->tag != TOKEN_SINGLE_QUOTE && next->tag != TOKEN_VARIABLE)
        return (false);
    return (true);
}

void concatenate_nodes(t_token *current, t_token *next)
{
    char *new_value;
    t_token *tmp;
    size_t len_current;
    size_t len_next;
    size_t total_len;
    
    if (!should_concatenate(current, next))
        return ;
    len_current = ft_strlen(current->value);
    len_next = ft_strlen(next->value);
    total_len = (len_current + len_next) + 1;
    new_value = malloc(total_len);
    ft_strlcpy(new_value, current->value, total_len);
    ft_strlcat(new_value, next->value, total_len);
    free(current->value);
    current->value = new_value;
    current->tag = TOKEN_WORD;
    current->space = next->space;
    tmp = next->next;
    free(next->value);
    free(next);
    current->next = tmp;
}

void concatenation(t_data *data)
{
    t_token *current;

    current = data->tokens;
    while (current)
    {
        if ((current->tag == TOKEN_SINGLE_QUOTE || current->tag == TOKEN_DOUBLE_QUOTE || current->tag == TOKEN_VARIABLE || current->tag == TOKEN_WORD) 
                && current->space == 0)
                concatenate_nodes(current, current->next);
        if ((current->tag == TOKEN_SINGLE_QUOTE || current->tag == TOKEN_DOUBLE_QUOTE || current->tag == TOKEN_VARIABLE || current->tag == TOKEN_WORD) 
                && current->space == 0 && should_concatenate(current, current->next))
            continue ;
        current = current->next;
    }
    
}
