/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:11:14 by nass              #+#    #+#             */
/*   Updated: 2025/06/24 16:00:41 by nyousfi          ###   ########.fr       */
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
	while (j < i)
	{
		beforevar[j] = input[j];
		j++;
	}
	beforevar[j] = 0;
	return (beforevar);
}

char	*recup_varname(char *input)
{
	int		i;
	int		j;
	int		y;
	char	*varname;

	i = 0;
	y = 0;
	j = 0;
	while (input[i] && input[i] != '$')
		i++;
	i++;
	if (input[i] == '?')
	{
		varname = malloc(2);
		varname[0] = '?';
		varname[1] = 0;
		return (varname);
	}
	j = i;
	while (input[i] && !ft_isspace(input[i]) && input[i] != '$')
		i++;
	varname = malloc((i - j) + 1);
	while (j < i)
		varname[y++] = input[j++];
	varname[y] = 0;
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
	while (input[i] && !ft_isspace(input[i]) && input[i] != '$' && input[i - 1] != '?')
		i++;
	j = i;
	while (input[i])
		i++;
	aftervar = malloc((i - j) + 1);
	while (j < i)
		aftervar[y++] = input[j++];
	aftervar[y] = 0;
	return (aftervar);
}

char	*recup_varvalue(char *varname)
{
	char	*varvalue;

	varvalue = getenv(varname);
	if (varvalue)
		return (ft_strdup(varvalue));
	return (ft_strdup(""));
}
