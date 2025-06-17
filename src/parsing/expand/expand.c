/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:18:39 by nass              #+#    #+#             */
/*   Updated: 2025/06/17 19:44:11 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void set_to_null(t_expand *expand)
{
    expand->aftervar = NULL;
    expand->beforevar = NULL;
    expand->varname = NULL;
    expand->varvalue = NULL;
}

char *set_empty(void)
{
    char *result;
    
    result = malloc(1);
    result[0] = 0;
    return (result);
}

void expand_token_value(char *input, t_token **token)
{
    char *result;
    t_token *tmp;
    t_expand expand;
    
    result = set_empty();
    set_to_null(&expand);
    expand.beforevar = recup_beforevar(input);
    expand.varname = recup_varname(input);
    expand.aftervar = recup_aftervar(input);
    expand.varvalue = recup_varvalue(expand.varname);
    free(expand.varname);
    free(input);
    result = ft_strjoin(result, expand.beforevar);
    free(expand.beforevar);
    result = ft_strjoin(result, expand.varvalue);
    free(expand.varvalue);
    result = ft_strjoin(result, expand.aftervar);
    free(expand.aftervar);
    tmp = *token;
    tmp->value = ft_strdup(result);
}

bool is_var(char *value)
{
    int i;

    i = 0;
    while (value[i])
    {
        if (value[i] == '$')
            return (true);
        i++;
    }
    return (false);
}

bool	is_redirection(t_type tag)
{
	return (tag == TOKEN_REDIR_IN || tag == TOKEN_REDIR_OUT
		|| tag == TOKEN_APPEND || tag == TOKEN_HEREDOC);
}

t_token *reverse_token_list(t_token *start, t_token *end)
{
	t_token *prev = NULL;
	t_token *current = start;
	t_token *next = NULL;
	t_token *after = end->next;

	while (current != after)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	start->next = after;

	return (prev);
}

void sort_redirections(t_token **head)
{
	t_token *current;
	t_token *prev;
    t_token *redir_start;
    t_token *redir_end;
    t_token *reversed;
    
    current = *head;
    prev = NULL;
    
	while (current)
	{
		if (is_redirection(current->tag))
		{
			redir_start = current;
			redir_end = current;

			while (redir_end->next && is_redirection(redir_end->next->tag))
				redir_end = redir_end->next;

			reversed = reverse_token_list(redir_start, redir_end);

			if (prev)
				prev->next = reversed;
			else
				*head = reversed;

			prev = redir_start;
			current = redir_start->next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void switch_nodes(t_token *a, t_token *b)
{
    t_type tmp_tag;
    char *tmp_value;
    bool tmp_space;
    
    if (!a || !b)
        return;
    
    tmp_tag = a->tag;
    tmp_value = a->value;
    tmp_space = a->space;
    
    a->tag = b->tag;
    a->value = b->value;
    a->space = b->space;
    
    b->tag = tmp_tag;
    b->value = tmp_value;
    b->space = tmp_space;
}

bool node_is_redir(t_token *node)
{
    if (!node)
        return (false);
    return (node->tag == TOKEN_REDIR_IN || node->tag == TOKEN_REDIR_OUT
		|| node->tag == TOKEN_APPEND || node->tag == TOKEN_HEREDOC);
}

bool node_is_word(t_token *node)
{
    if (!node)
        return (false);
    return (node->tag == TOKEN_SINGLE_QUOTE || node->tag == TOKEN_DOUBLE_QUOTE 
            || node->tag == TOKEN_WORD);
}

bool node_is_operator(t_token *node)
{
    if (!node)
        return (false);
    return (node->tag == TOKEN_PIPE || node->tag == TOKEN_SINGLE_QUOTE || node->tag == TOKEN_DOUBLE_QUOTE);
}

void move_start_redir(t_token **head)
{
    t_token *current;
    bool is_start;

    is_start = true;
    current = *head;
    while (current)
    {
        while (node_is_redir(current) && node_is_redir(current->next))
            current = current->next;
        if (node_is_redir(current) && node_is_word(current->next) && is_start)
        {
            is_start = false;
            switch_nodes(current, current->next);
            current = *head;
            continue ;
        }
        if (node_is_operator(current))
            is_start = true;
        current = current->next;
    }
}
void expander(t_data *data)
{
    t_token *tmp;
    
    tmp = data->tokens;
    while (tmp)
    {
        if (tmp->tag == TOKEN_VARIABLE || tmp->tag == TOKEN_DOUBLE_QUOTE || tmp->tag == TOKEN_WORD)
        {
            while (is_var(tmp->value))
                expand_token_value(tmp->value, &tmp);
        }
        tmp = tmp->next;
    }
	change_redir_value(data);
    concatenation(data);
    move_start_redir(&data->tokens);
    sort_redirections(&data->tokens);
}
