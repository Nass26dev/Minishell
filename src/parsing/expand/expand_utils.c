/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:11:14 by nass              #+#    #+#             */
/*   Updated: 2025/06/30 13:36:16 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*recup_beforevar(char *input)
{
	int		i;
	int		j;
	char	*beforevar;

	i = 0;
	j = 0;
	while (input[i] && input[i] != '$')
		i++;
	beforevar = malloc(i + 1);
	if (!beforevar)
		return (NULL);
	while (j < i)
	{
		beforevar[j] = input[j];
		j++;
	}
	beforevar[j] = 0;
	return (beforevar);
}

void	start_index(t_triple_index *ind, char *input)
{
	ind->i = 0;
	ind->y = 0;
	ind->j = 0;
	while (input[ind->i] && input[ind->i] != '$')
		ind->i++;
	ind->i++;
}

char	*recup_varname(char *input)
{
	t_triple_index	ind;
	char			*varname;

	start_index(&ind, input);
	if (input[ind.i] == '?')
	{
		varname = malloc(2);
		if (!varname)
			return (NULL);
		varname[0] = '?';
		varname[1] = 0;
		return (varname);
	}
	ind.j = ind.i;
	while (input[ind.i] && !ft_isspace(input[ind.i]) && input[ind.i] != '$'
		&& input[ind.i] != '"' && input[ind.i] != '\'')
		ind.i++;
	varname = malloc((ind.i - ind.j) + 1);
	if (!varname)
		return (NULL);
	while (ind.j < ind.i)
		varname[ind.y++] = input[ind.j++];
	varname[ind.y] = 0;
	return (varname);
}

char	*recup_aftervar(char *input)
{
	int		i;
	int		j;
	int		y;
	char	*aftervar;

	i = 0;
	j = 0;
	y = 0;
	while (input[i] && input[i] != '$')
		i++;
	i++;
	while (input[i] && !ft_isspace(input[i]) && input[i] != '$'
		&& input[i - 1] != '?' && input[i] != '"' && input[i] != '\'')
		i++;
	j = i;
	while (input[i])
		i++;
	aftervar = malloc((i - j) + 1);
	if (!aftervar)
		return (NULL);
	while (j < i)
		aftervar[y++] = input[j++];
	aftervar[y] = 0;
	return (aftervar);
}

char	*recup_varvalue(char *varname, t_data *data)
{
	char	*varvalue;

	varvalue = ft_getenv(varname, data->shell->env->data);
	if (varvalue)
		return (ft_strdup(varvalue));
	return (ft_strdup(""));
}
