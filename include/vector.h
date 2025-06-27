#ifndef VECTOR_H
# define VECTOR_H

# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_vector
{
	char	**data;
	int		count;
	int		capacity;
}			t_vector;

/*vector.c*/
t_vector	*vector_create(int initial_capacity);
bool		vector_add(t_vector *vector, char *str);
void		free_vector(t_vector *vector);

#endif