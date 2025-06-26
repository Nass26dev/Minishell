/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:07:55 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/26 17:38:58 by eelissal         ###   ########lyon.fr   */
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
	if (ret == 0 && node->tag == TOKEN_AND)
		ret = exec_node(exec);
	else if (ret != 0 && node->tag == TOKEN_OR)
		ret = exec_node(exec);
	exec->current = node;
	return (ret);
}
