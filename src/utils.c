/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:34:07 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/30 15:14:39 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	write_fd(char *cmd1, char *cmd2, char *msg, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(cmd1, fd);
	if (cmd1)
		write(fd, ": ", STDERR_FILENO);
	ft_putstr_fd(cmd2, fd);
	if (cmd2)
		write(fd, ": ", STDERR_FILENO);
	ft_putendl_fd(msg, fd);
}

void	set_to_null(t_expand *expand)
{
	expand->aftervar = NULL;
	expand->beforevar = NULL;
	expand->varname = NULL;
	expand->varvalue = NULL;
}

char	*set_empty(void)
{
	char	*result;

	result = malloc(1);
	if (!result)
		return (NULL);
	result[0] = 0;
	return (result);
}

char	*free_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	str = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	j = 0;
	while (s1[j])
		str[++i] = s1[j++];
	j = 0;
	while (s2[j])
		str[++i] = s2[j++];
	str[++i] = 0;
	free(s1);
	free(s2);
	return (str);
}

char	*ft_getenv(char *search, char **env)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(search);
	while (env[++i])
	{
		if (ft_strncmp(env[i], search, len) == 0 && env[i][len] == '=')
			return (env[i] + (len + 1));
	}
	return (NULL);
}
