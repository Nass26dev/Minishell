/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:07:55 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/27 17:41:11 by nyousfi          ###   ########.fr       */
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
	ret = exec_node(exec);
	exec->current = node->right;
	if (ret == 0 && node->tag == AND)
		ret = exec_node(exec);
	else if (ret != 0 && node->tag == OR)
		ret = exec_node(exec);
	exec->current = node;
	return (ret);
}
