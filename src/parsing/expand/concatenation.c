/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:12:06 by nass              #+#    #+#             */
/*   Updated: 2025/06/16 17:04:07 by nyousfi          ###   ########.fr       */
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

void concatenate_nodes_with_spaces(t_token *current, t_token *next)
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
    total_len = (len_current + len_next) + 2;
    new_value = malloc(total_len);
    ft_strlcpy(new_value, current->value, total_len);
    ft_strlcat(new_value, " ", total_len);
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

void concatenate_nodes_after_redir(t_token *current, t_token *saved, t_token *last_dir)
{
    char *new_value;
    t_token *tmp;
    size_t len_saved;
    size_t len_current;
    size_t total_len;
    
    if (!should_concatenate(saved, current))
        return ;
    len_saved = ft_strlen(saved->value);
    len_current = ft_strlen(current->value);
    total_len = (len_saved + len_current) + 2;
    new_value = malloc(total_len);
    ft_strlcpy(new_value, saved->value, total_len);
    ft_strlcat(new_value, " ", total_len);
    ft_strlcat(new_value, current->value, total_len);
    free(saved->value);
    saved->value = new_value;
    saved->tag = TOKEN_WORD;
    saved->space = current->space;
    tmp = current->next;
    free(current->value);
    free(current);
    last_dir->next = tmp;
}

void concatenate_args(t_data *data)
{
    t_token *current;
    bool concat;
    bool is_redir;
    bool savestat;
    t_token *saved;
    t_token *last_redir;

    is_redir = false;
    saved = NULL;
    concat = false;
    current = data->tokens;
    while (current)
    {
        // gerer le cas ou echo < in salut
        if (current->tag != TOKEN_SINGLE_QUOTE && current->tag != TOKEN_DOUBLE_QUOTE && current->tag != TOKEN_WORD 
            && current->tag != TOKEN_REDIR_IN && current->tag != TOKEN_REDIR_OUT && current->tag != TOKEN_APPEND
            && current->tag != TOKEN_HEREDOC)
        {
            concat = false;
            is_redir = false;
            savestat = false;
        }
        else if (current->tag == TOKEN_REDIR_IN || current->tag == TOKEN_REDIR_OUT || current->tag == TOKEN_APPEND || current->tag == TOKEN_HEREDOC)
        {
            is_redir = true;
            last_redir = current;
        }
        else if ((current->tag == TOKEN_SINGLE_QUOTE || current->tag == TOKEN_DOUBLE_QUOTE || current->tag == TOKEN_WORD) && concat == false)
        {
            concat = true;
        }
        else if ((current->tag == TOKEN_SINGLE_QUOTE || current->tag == TOKEN_DOUBLE_QUOTE || current->tag == TOKEN_WORD) && concat == true)
        {
            if (savestat == false)
            {
                savestat = true;
                saved = current;
            }
            if (is_redir)
            {
                concatenate_nodes_after_redir(current, saved, last_redir);
            }
            else if (current->next && (current->next->tag == TOKEN_SINGLE_QUOTE 
                || current->next->tag == TOKEN_DOUBLE_QUOTE || current->next->tag == TOKEN_WORD))
            {
                concatenate_nodes_with_spaces(current, current->next);
                continue ;
            }
            else
                saved = current;
        }
        current = current->next;
    }
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
    concatenate_args(data);
}
