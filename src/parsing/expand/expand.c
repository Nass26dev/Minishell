/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:18:39 by nass              #+#    #+#             */
/*   Updated: 2025/06/07 19:56:24 by nass             ###   ########.fr       */
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
    concatenation(data);
	change_redir_value(data);
}
