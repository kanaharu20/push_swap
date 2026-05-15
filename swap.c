/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 16:18:02 by kyonaha           #+#    #+#             */
/*   Updated: 2026/05/15 17:09:10 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_list **node_ptr)
{
	t_list	*node;
	t_list	*next;

	node = *node_ptr;
	if (node != NULL && node->next != NULL)
	{
		next = node->next;
		node->next = next->next;
		next->next = node;
		*node_ptr = next;
	}
}

void	sa(t_list **a_node, t_data *bench_data)
{
	swap(a_node);
	write(1, "sa\n", 3);
	bench_data->sa_cnt++;
}

void	sb(t_list **b_node, t_data *bench_data)
{
	swap(b_node);
	write(1, "sb\n", 3);
	bench_data->sb_cnt++;
}

void	ss(t_list **a_node, t_list **b_node, t_data *bench_data)
{
	swap(a_node);
	swap(b_node);
	write(1, "ss\n", 3);
	bench_data->ss_cnt++;
}
