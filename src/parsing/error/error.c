/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:03:29 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/06 17:20:40 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void error_checker(t_data *data)
{
	(void)data;
}

void syntax_error(t_data *data, char *error)
{
	free_tokens(&data->tokens);
	printf("%s\n", error);
	data->error = true;
}
