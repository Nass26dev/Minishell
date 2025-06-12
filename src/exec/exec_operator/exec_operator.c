/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:07:55 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/12 15:53:58 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_operator(t_exec *exec)
{
	t_ast	*node;
	int		ret;

	ret = 1;
	node = exec->current;
	exec->current = node->left;
	// if (node->tag == AND)
	// 	printf("AND: exec process left\n");
	// else
	// 	printf("OR: exec process left\n");
	ret = exec_node(exec);
	exec->current = node->right;
	if (ret == 0 && node->tag == AND)
	{
		// printf("AND: exec process right\n");
		ret = exec_node(exec);
	}
	// else if (ret != 0 && node->tag == AND)
	// 	printf("AND: exec process right could not be done because exec process left failed\n");
	else if (ret != 0 && node->tag == OR)
	{
		// printf("OR: exec process right\n");
		ret = exec_node(exec);
	}
	// else if (ret == 0 && node->tag == OR)
	// 	printf("OR: exec process right could not be done because exec process left suceeded\n");
	exec->current = node;
	return (ret);
}
