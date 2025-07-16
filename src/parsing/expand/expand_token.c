/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:34:07 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 17:41:11 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	recup_expand(t_expand *expand, char *input)
{
	expand->beforevar = recup_beforevar(input);
	if (!expand->beforevar)
		return (true);
	expand->varname = recup_varname(input);
	if (!expand->varname)
	{
		free(expand->beforevar);
		return (true);
	}
	expand->aftervar = recup_aftervar(input);
	if (!expand->aftervar)
	{
		free(expand->beforevar);
		free(expand->varname);
		return (true);
	}
	return (false);
}

bool	create_result(char **result, t_expand *expand)
{
	*result = free_strjoin(*result, expand->beforevar);
	if (!(*result))
	{
		free(expand->beforevar);
		free(expand->varvalue);
		free(expand->aftervar);
		return (1);
	}
	*result = free_strjoin(*result, expand->varvalue);
	if (!(*result))
	{
		free(expand->varvalue);
		free(expand->aftervar);
		return (1);
	}
	*result = free_strjoin(*result, expand->aftervar);
	if (!(*result))
	{
		free(expand->aftervar);
		return (1);
	}
	return (0);
}

bool	get_varvalue(t_data *data, t_expand *expand)
{
	if (expand->varname[0] == '?')
		expand->varvalue = ft_itoa(data->shell->status);
	else
		expand->varvalue = recup_varvalue(expand->varname, data);
	free(expand->varname);
	if (!expand->varvalue)
	{
		free(expand->beforevar);
		free(expand->aftervar);
		return (1);
	}
	return (0);
}

bool	init_result(char **result, t_expand *expand)
{
	*result = set_empty();
	if (!(*result))
	{
		free(expand->beforevar);
		free(expand->varvalue);
		free(expand->aftervar);
		return (1);
	}
	return (0);
}

int	expand_token_value(char *input, t_token **token, t_data *data)
{
	char		*result;
	t_token		*tmp;
	t_expand	expand;

	set_to_null(&expand);
	if (recup_expand(&expand, input))
		return (1);
	if (get_varvalue(data, &expand))
		return (1);
	if (init_result(&result, &expand))
		return (1);
	if (create_result(&result, &expand))
		return (1);
	tmp = *token;
	tmp->value = ft_strdup(result);
	free(result);
	if (!tmp->value)
		return (1);
	free(input);
	tmp->tag = WORD;
	return (0);
}
