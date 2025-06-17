/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:18:39 by nass              #+#    #+#             */
/*   Updated: 2025/06/17 17:26:52 by nass             ###   ########.fr       */
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
    sort_redirections(&data->tokens);
}
