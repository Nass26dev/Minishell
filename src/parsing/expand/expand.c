/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:18:39 by nass              #+#    #+#             */
/*   Updated: 2025/06/23 17:32:18 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		return (NULL);
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

void	expand_token_value(char *input, t_token **token, int status)
{
	char		*result;
	t_token		*tmp;
	t_expand	expand;

	result = set_empty();
	set_to_null(&expand);
	expand.beforevar = recup_beforevar(input);
	expand.varname = recup_varname(input, status);
	expand.aftervar = recup_aftervar(input);
	if (input[1] == '?' && !input[2])
		expand.varvalue = ft_strdup(expand.varname);
	else
		expand.varvalue = recup_varvalue(expand.varname);
	free(expand.varname);
	free(input);
	result = free_strjoin(result, expand.beforevar);
	result = free_strjoin(result, expand.varvalue);
	result = free_strjoin(result, expand.aftervar);
	tmp = *token;
	tmp->value = ft_strdup(result);
	free(result);
	tmp->tag = TOKEN_WORD;
}

bool	is_var(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

bool	is_redirection(t_tag tag)
{
	return (tag == TOKEN_REDIR_IN || tag == TOKEN_REDIR_OUT
		|| tag == TOKEN_APPEND || tag == TOKEN_HEREDOC);
}

t_token	*reverse_token_list(t_token *start, t_token *end)
{
	t_token	*prev;
	t_token	*current;
	t_token	*next;
	t_token	*after;

	prev = NULL;
	current = start;
	next = NULL;
	after = end->next;
	while (current != after)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	start->next = after;
	return (prev);
}

void	sort_redirections(t_token **head)
{
	t_token	*current;
	t_token	*prev;
	t_token	*redir_start;
	t_token	*redir_end;
	t_token	*reversed;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (is_redirection(current->tag))
		{
			redir_start = current;
			redir_end = current;
			while (redir_end->next && is_redirection(redir_end->next->tag))
				redir_end = redir_end->next;
			reversed = reverse_token_list(redir_start, redir_end);
			if (prev)
				prev->next = reversed;
			else
				*head = reversed;
			prev = redir_start;
			current = redir_start->next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	switch_nodes(t_token *a, t_token *b)
{
	t_tag	tmp_tag;
	char	*tmp_value;
	bool	tmp_space;

	if (!a || !b)
		return ;
	tmp_tag = a->tag;
	tmp_value = a->value;
	tmp_space = a->space;
	a->tag = b->tag;
	a->value = b->value;
	a->space = b->space;
	b->tag = tmp_tag;
	b->value = tmp_value;
	b->space = tmp_space;
}

bool	node_is_redir(t_token *node)
{
	if (!node)
		return (false);
	return (node->tag == TOKEN_REDIR_IN || node->tag == TOKEN_REDIR_OUT
		|| node->tag == TOKEN_APPEND || node->tag == TOKEN_HEREDOC);
}

bool	node_is_word(t_token *node)
{
	if (!node)
		return (false);
	return (node->tag == TOKEN_SINGLE_QUOTE || node->tag == TOKEN_DOUBLE_QUOTE
		|| node->tag == TOKEN_WORD);
}

bool	node_is_operator(t_token *node)
{
	if (!node)
		return (false);
	return (node->tag == TOKEN_PIPE || node->tag == TOKEN_OR
		|| node->tag == TOKEN_AND);
}

void	move_start_redir(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (node_is_redir(current) && node_is_word(current->next))
		{
			switch_nodes(current, current->next);
			current = *head;
		}
		else
			current = current->next;
	}
}

void	delete_node(t_token **head, t_token *node_to_delete)
{
	t_token *prev;

	if (!head || !*head || !node_to_delete)
		return;

	// Si le nœud à supprimer est la tête
	if (*head == node_to_delete)
	{
		*head = node_to_delete->next;
		free(node_to_delete->value); // libère la chaîne si allouée dynamiquement
		free(node_to_delete);
		return;
	}

	prev = *head;
	while (prev && prev->next != node_to_delete)
		prev = prev->next;

	// Si le nœud a été trouvé
	if (prev && prev->next == node_to_delete)
	{
		prev->next = node_to_delete->next;
		free(node_to_delete->value); // libère la chaîne si allouée dynamiquement
		free(node_to_delete);
	}
}

int get_nb_args(t_token *node)
{
	t_token *current;
	int i;

	i = 0;
	current = node;
	while (current && !node_is_operator(current))
	{
		if (node_is_word(current))
			i++;
		current = current->next;
	}
	return (i);
}

void get_cmd(t_token **node)
{
	t_token *current;
	t_token *prev;
	char **cmd;
	int i;

	i = 0;
	cmd = malloc(sizeof(char *) * (get_nb_args(*node) + 1));
	current = *node;
	cmd[i++] = ft_strdup(current->value);
	prev = current;
	current = current->next;
	while (current && !node_is_operator(current))
	{
		if (node_is_word(current))
		{
			cmd[i++] = ft_strdup(current->value);
			delete_node(node, current);
			current = prev;
		}
		current = current->next;
	}
	cmd[i] = NULL;
	current = *node;
	current->cmd = cmd;
	current->tag = TOKEN_CMD;
}

void create_cmd(t_data *data)
{
	t_token *current;

	current = data->tokens;
	while (current)
	{
		if (node_is_word(current))
			get_cmd(&current);
		current = current->next;
	}
}

void	expander(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (tmp->tag == TOKEN_VARIABLE || tmp->tag == TOKEN_DOUBLE_QUOTE
			|| tmp->tag == TOKEN_WORD)
		{
			while (is_var(tmp->value))
				expand_token_value(tmp->value, &tmp, data->status);
		}
		tmp = tmp->next;
	}
	change_redir_value(data);
	concatenation(data);
	move_start_redir(&data->tokens);
	sort_redirections(&data->tokens);
	create_cmd(data);
}
