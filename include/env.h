/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:52:06 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/14 16:17:00 by eelissal         ###   ########lyon.fr   */
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
void			unlink_heredoc(t_hd_token *heredoc);
void			free_shell(t_shell *shell);

#endif