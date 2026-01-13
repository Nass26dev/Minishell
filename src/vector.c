/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:59:45 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/27 17:28:00 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	*vector_create(int initial_capacity)
{
	t_vector	*vector;
	int			i;

	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->data = malloc(sizeof(char *) * initial_capacity);
	if (!vector->data)
	{
		free(vector);
		return (NULL);
	}
	vector->count = 0;
	vector->capacity = initial_capacity;
	i = 0;
	while (i < initial_capacity)
	{
		vector->data[i] = NULL;
		i++;
	}
	return (vector);
}

static bool	vector_resize(t_vector *vector)
{
	char	**new_data;
	int		i;

	new_data = malloc(sizeof(char *) * (vector->capacity * 2));
	if (!new_data)
		return (false);
	i = 0;
	while (i < vector->count)
	{
		new_data[i] = vector->data[i];
		i++;
	}
	while (i < vector->capacity * 2)
	{
		new_data[i] = NULL;
		i++;
	}
	free(vector->data);
	vector->data = new_data;
	vector->capacity *= 2;
	return (true);
}

bool	vector_add(t_vector *vector, char *str)
{
	char	*dup;

	if (!vector || !str)
		return (false);
	if (vector->count >= vector->capacity - 1)
	{
		if (!vector_resize(vector))
			return (false);
	}
	dup = ft_strdup(str);
	if (!dup)
		return (false);
	vector->data[vector->count] = dup;
	vector->count++;
	vector->data[vector->count] = NULL;
	return (true);
}

void	free_vector(t_vector *vector)
{
	int	i;

	if (!vector)
		return ;
	if (vector->data)
	{
		i = 0;
		while (i < vector->count)
		{
			if (vector->data[i])
				free(vector->data[i]);
			i++;
		}
		free(vector->data);
	}
	free(vector);
}
