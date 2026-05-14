/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyonaha <kyonaha@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 13:43:06 by kyonaha           #+#    #+#             */
/*   Updated: 2026/05/14 13:59:17 by kyonaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_rotate(t_list **node_ptr)
{
	t_list	*first;
	t_list	*last;
	t_list	*tmp;

	first = *node_ptr;
	last = *node_ptr;
	tmp = *node_ptr;
	while (last->next != NULL)
		last = last->next;
	while (tmp->next != last)
		tmp = tmp->next;
	tmp->next = NULL;
	last->next = first;
	*node_ptr = last;
}

void	rra(t_list **a_node)
{
	reverse_rotate(a_node);
	write(1, "rra\n", 4);
}

void	rrb(t_list **b_node)
{
	reverse_rotate(b_node);
	write(1, "rrb\n", 4);
}

void	rrr(t_list **a_node, t_list **b_node)
{
	reverse_rotate(a_node);
	reverse_rotate(b_node);
	write(1, "rrr\n", 4);
}
