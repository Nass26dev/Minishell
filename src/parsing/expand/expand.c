/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:18:39 by nass              #+#    #+#             */
/*   Updated: 2025/06/17 17:02:20 by nass             ###   ########.fr       */
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

	while (current && current != end->next)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return (prev); // nouvelle tête de la sous-liste inversée
}

void	sort_redir(t_token **head)
{
    t_token_sort tok;
	tok.current = *head;
	tok.prev = NULL;

	while (tok.current)
	{
		if (is_redirection(tok.current->tag))
		{
			tok.redir_start = tok.current;
			tok.redir_end = tok.current;

			while (tok.redir_end->next && is_redirection(tok.redir_end->next->tag))
				tok.redir_end = tok.redir_end->next;

			tok.after = tok.redir_end->next;
			tok.reversed = reverse_token_list(tok.redir_start, tok.redir_end);

			if (!tok.prev)
				*head = tok.reversed;
			else
				tok.prev->next = tok.reversed;

			tok.redir_start->next = tok.after;
			tok.current = tok.after;
		}
		else
		{
			tok.prev = tok.current;
			tok.current = tok.current->next;
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
    sort_redir(&data->tokens);
}
