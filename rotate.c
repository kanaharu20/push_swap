/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:36:58 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/14 12:51:17 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_list **node_ptr)
{
	t_list	*first;
	t_list	*second;
	t_list	*tmp;

	tmp = *node_ptr;
	first = *node_ptr;
	second = first->next;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = first;
	first->next = NULL;
	*node_ptr = second;
}
