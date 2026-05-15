/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_based_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 15:32:44 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 15:02:25 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	root(int lst_count)
{
	int	r;

	r = 0;
	while ((long)(r * r) <= 2147483647)
	{
		if ((r * r == lst_count))
			return (r);
		r++;
	}
	return (-1);
}

static void	call_rotate_push(t_list **a_lst, t_list **b_lst, int rotate_count)
{
	while (rotate_count >= 0)
	{
		rb(b_lst);
		rotate_count--;
	}
	pa(a_lst, b_lst);
}

static void	call_reverse(t_list **a_lst, t_list **b_lst, int reverse_count)
{
	while (reverse_count >= 0)
	{
		rrb(b_lst);
		reverse_count--;
	}
}

void	chunk_based_sort2(t_list **a_lst, t_list **b_lst, int count)
{
	int		rotate_count;
	t_list	*lst;

	while (count >= 0)
	{
		rotate_count = 0;
		lst = *a_lst;
		while (lst->next != NULL)
		{
			if (count == lst->rank)
				break ;
			rotate_count++;
			lst = lst->next;
		}
		call_rotate_push(a_lst, b_lst, rotate_count);
		call_reverse(a_lst, b_lst, rotate_count);
		count --;
	}
}

void	chunk_based_sort(t_list **a_lst, t_list **b_lst)
{
	t_list	*lst;
	int		count;
	int		i;
	int		r;

	i = 0;
	count = lst_count(*a_lst);
	r = root(count);
	while (i <= r)
	{
		lst = *a_lst;
		while (lst)
		{
			if (i * r <= lst->rank && lst->rank < (i + 1) * r)
				pb(a_lst, b_lst);
			lst = lst->next;
		}
		i++;
	}
	chunk_based_sort2(a_lst, b_lst, count);
}
