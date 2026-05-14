/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:36:58 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/14 14:02:55 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_list **node_ptr)
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

void	ra(t_list **a_lst)
{
	rotate(a_lst);
	write(1, "ra\n", 3);
}

void	rb(t_list **b_lst)
{
	rotate(b_lst);
	write(1, "rb\n", 3);
}

void	rr(t_list **a_lst, t_list **b_lst)
{
	rotate(a_lst);
	rotate(b_lst);
	write(1, "rr\n", 3);
}
