/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:38:12 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/16 12:59:05 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	add_filename_to_lst(t_hd **heredoc, char *filename)
{
	t_hd	*new_node;
	t_hd	*current;

	new_node = malloc(sizeof(t_hd));
	if (!new_node)
		return (true);
	new_node->filename = ft_strdup(filename);
	if (!new_node->filename)
	{
		free(new_node);
		return (true);
	}
	new_node->next = NULL;
	if (!*heredoc)
	{
		*heredoc = new_node;
		return (false);
	}
	current = *heredoc;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (false);
}

bool	readline_loop(int fd, char *delimiter)
{
	char	*line;
	int		len;

	line = readline("> ");
	if (!line || ft_strcmp(line, delimiter) == 0)
		return (true);
	if (g_received_signal == SIGINT)
	{
		free(line);
		g_received_signal = 0;
		return (true);
	}
	len = ft_strlen(line);
	write(fd, line, len);
	write(fd, "\n", 1);
	free(line);
	return (false);
}

void	fill_heredoc(t_data *data, char *filename, char *delimiter)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR, 0777);
	if (fd < 0)
	{
		free(filename);
		malloc_error(data);
		return ;
	}
	while (1)
	{
		if (readline_loop(fd, delimiter))
			break ;
	}
	free(delimiter);
	close(fd);
}

bool	change_node(t_token **current, t_data *data, char *delimiter)
{
	t_token	*node;
	char	*filename;

	filename = create_file();
	if (!filename)
		return (true);
	if (add_filename_to_lst(&data->heredoc, filename))
	{
		free(filename);
		return (true);
	}
	node = *current;
	setup_heredoc_signals();
	rl_event_hook = event_hook;
	fill_heredoc(data, filename, delimiter);
	rl_event_hook = NULL;
	setup_interactive_signals();
	node->tag = REDIR_IN;
	node->value = filename;
	return (false);
}

int	change_heredoc(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (current->tag == HEREDOC)
		{
			if (change_node(&current, data, current->value))
				malloc_error(data);
			if (data->shell->status == 130)
			{
				free_tokens(&data->tokens);
				free_all_heredocs(&data->heredoc);
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}
