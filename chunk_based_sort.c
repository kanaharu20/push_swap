/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_based_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 15:32:44 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 15:43:56 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	root(int lst_count)
{
	int	r;

	r = 0;
	while ((long)(r * r) <= 2147483647)
	{
		if ((r * r > lst_count))
			break ;
		r++;
	}
	return (r);
}

static void	call_rotate_push(t_list **a_lst, t_list **b_lst, int rotate_count,
		t_data *bench_data)
{
	while (rotate_count >= 0)
	{
		rb(b_lst, bench_data);
		rotate_count--;
	}
	pa(a_lst, b_lst, bench_data);
}

static void	call_reverse(t_list **a_lst, t_list **b_lst, int reverse_count,
		t_data *bench_data)
{
	while (reverse_count >= 0)
	{
		rrb(b_lst, bench_data);
		reverse_count--;
	}
}

void	chunk_based_sort2(t_list **a_lst, t_list **b_lst, int count,
		t_data *bench_data)
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
		call_rotate_push(a_lst, b_lst, rotate_count, bench_data);
		call_reverse(a_lst, b_lst, rotate_count, bench_data);
		count--;
	}
}

void	chunk_based_sort(t_list **a_lst, t_list **b_lst, t_data *bench_data)
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
				pb(a_lst, b_lst, bench_data);
			lst = lst->next;
		}
		i++;
	}
	chunk_based_sort2(a_lst, b_lst, count, bench_data);
}
