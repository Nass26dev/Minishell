/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:01:22 by eelissal          #+#    #+#             */
/*   Updated: 2024/11/23 18:57:20 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*i;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	i = *lst;
	while (i)
	{
		tmp = i->next;
		del(i->content);
		free(i);
		i = tmp;
	}
	*lst = NULL;
}
