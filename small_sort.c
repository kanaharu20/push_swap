/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:20:52 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/19 16:26:01 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	small_sort(t_list *a_lst, t_data *bench_data)
{
	int	x;
	int	y;
	int	z;

	x = a_lst->rank;
	y = a_lst->next->rank;
	z = a_lst->next->next->rank;
	if (x < y && y > z && x < z)
	{
		ra(&a_lst, bench_data);
		sa(&a_lst, bench_data);
	}
	else if (x > y && y < z && x < z)
		sa(&a_lst, bench_data);
	else if (x < y && y > z && x > z)
		ra(&a_lst, bench_data);
	else if (x > y && y < z && x > z)
		rra(&a_lst, bench_data);
	else if (x > y && y > z && x > z)
	{
		sa(&a_lst, bench_data);
		ra(&a_lst, bench_data);
	}
}
void	small_sort3(t_list *a_lst, t_list *b_lst, t_data *bench_data)
{
	t_list	*tmp;

	tmp = a_lst;
	while (tmp != NULL)
	{
		if (tmp->rank == 0 || tmp->rank == 1)
			pa(&a_lst, &b_lst, bench_data);
		ra(&a_lst, bench_data);
		tmp = tmp->next;
	}
	small_sort(a_lst, bench_data);
	if (b_lst->rank > b_lst->next->content)
		sb(&a_lst, bench_data);
	pb(&a_lst, &b_lst, bench_data);
	pb(&a_lst, &b_lst, bench_data);
}
void	small_sort2(t_list *a_lst, t_list *b_lst, t_data *bench_data)
{
	t_list	*tmp;

	tmp = a_lst;
	while (tmp != NULL)
	{
		if (a_lst->rank == 0)
		{
			pa(&a_lst, &b_lst, bench_data);
			break;
		}
		ra(&a_lst, bench_data);
		tmp = tmp->next;
	}
	small_sort(a_lst, bench_data);
	pb(&a_lst, &b_lst, bench_data);
}

void	base_sort(t_list *a_lst, t_data *bench_data)
{
	int		count;
	t_list	*b_lst;

	b_lst = NULL;
	count = lst_count(a_lst);
	if (count == 2)
	{
		if (a_lst->rank > a_lst->next->content)
			sa(&a_lst, bench_data);
	}
	else if (count == 3)
		small_sort(a_lst, bench_data);
	else if (count == 4)
		small_sort2(a_lst, b_lst, bench_data);
	else if (count == 5)
		small_sort3(a_lst, b_lst, bench_data);
}
