/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyonaha <kyonaha@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:25:22 by kyonaha           #+#    #+#             */
/*   Updated: 2026/05/14 12:49:14 by kyonaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_list **to, t_list **from)
{
	t_list	*to_node;
	t_list	*from_node;

	to_node = *to;
	from_node = *from;
	if (from_node != NULL)
	{
		*from = from_node->next;
		from_node->next = to_node;
		*to = from_node;
	}
}

void	pa(t_list **a_node, t_list **b_node)
{
	push(a_node, b_node);
	write(1, "pa\n", 3);
}

void	pb(t_list **a_node, t_list **b_node)
{
	push(b_node, a_node);
	write(1, "pb\n", 3);
}
