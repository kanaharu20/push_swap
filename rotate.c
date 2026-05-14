/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:36:58 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/14 13:47:38 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void rotate(t_list **node_ptr)
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

void	ra(t_list **a_node)
{
	rotate(a_node);
	write(1, "ra\n", 3);
}

void	ra(t_list **b_node)
{
	rotate(b_node);
	write(1, "rb\n", 3);
}

void	rr(t_list **a_node, t_list **b_node)
{
	rotate(a_node);
	rotate(b_node);
	write(1, "rr\n", 3);
}
