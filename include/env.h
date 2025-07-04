/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:52:06 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/04 18:44:06 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "vector.h"

typedef struct s_hd_token
{
	char			*filename;
	struct s_hd_token	*next;
}				t_hd_token;

typedef struct s_shell
{
	t_vector	*env;
	t_hd_token	*heredoc;
	int			status;
}				t_shell;

/*env.c*/
bool			init_shell(t_shell *shell, char **envp);
char			*get_env(t_vector *env, char *to_search);
void			free_shell(t_shell *shell);

#endif