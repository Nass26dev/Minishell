/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:38:12 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/15 16:48:42 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

static char	*add_num(int i)
{
	char	*temp;
	char	*filename;

	temp = ft_itoa(i);
	if (!temp)
		return (NULL);
	filename = ft_strjoin(BASE_FILENAME, temp);
	if (!filename)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (filename);
}

static char	*create_file(void)
{
	int		fd;
	char	*filename;
	int		i;

	i = 1;
	while (i <= MAX_TRIES)
	{
		if (i == 1)
			filename = ft_strdup(BASE_FILENAME);
		else
			filename = add_num(i);
		if (!filename)
			return (NULL);
		fd = open(filename, O_CREAT | O_EXCL, 0777);
		if (fd != -1)
		{
			close(fd);
			return (filename);
		}
		i++;
		free(filename);
	}
	return (NULL);
}

bool add_filename_to_lst(t_hd_token **heredoc, char *filename)
{
	t_hd_token	*new_node;
	t_hd_token	*current;

	new_node = malloc(sizeof(t_hd_token));
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

void fill_heredoc(t_data *data, char *filename, char *delimiter)
{
	int		fd;
	char *line;
	int len;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR, 0777);
	if (fd < 0)
	{
		free(filename);
		malloc_error(data);
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		if (g_received_signal == SIGINT)
		{
			free(line);
			g_received_signal = 0;
			data->shell->status = 130;
			break ;
		}
		len = ft_strlen(line);
		write(fd, line, len);
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}
bool change_node(t_token **current, t_data *data, char *delimiter)
{
	t_token	*node;
	char *filename;

	filename = create_file();
	if (!filename)
		return (true);
	if (!add_filename_to_lst(&data->heredoc, filename))
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
	node->value = ft_strdup(filename);
	return (false);
}

void change_heredoc(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (current->tag == HEREDOC)
		{
			if (!change_node(&current, data, current->value))
				malloc_error(data);
		}
		current = current->next;
	}
}
