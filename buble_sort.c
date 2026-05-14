/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buble_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 13:43:24 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/14 14:02:55 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_node(t_list *lst)
{
	t_list	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

void	buble_sort(t_list **a_lst, t_list **b_lst)
{
	int count_node = count(a_lst);
	t_list *a_next;
	int i = 0;
	int j = 0;
	a_next = (*a_lst)->next;
	while (i < count_node)
	{
		while (j < count_node)
		{
			if ((*a_lst)->content > a_next->content)

				j++;
		}
		i++;
	}
}