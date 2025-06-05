/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:53:44 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/05 11:29:43 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
# include <limits.h>
# include <unistd.h>

typedef struct s_data
{
	
}			t_data;

// loop.c
void minishell_loop(void);
// line.c
char *get_line_and_add_to_historical(t_data *data);
// error_checker.c
void error_checker(t_data *data);

#endif