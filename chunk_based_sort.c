/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_based_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 15:32:44 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/14 16:59:48 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	lst_count(t_list *lst)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = lst;
	while (tmp->next != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
static int	root(int lst_count)
{
	int	r;

	r = 0;
	while ((long)(r * r) <= 2147483647)
	{
		if ((r * r == lst_count))
			return (r);
	}
	return (-1);
}
static void	call_rotate_push(t_list **a_lst, t_list **b_lst, int rotate_count)
{
	while(rotate_count>=0)
	{
		rb(*b_lst);
		rotate_count--;
	}
	pa(a_list ,b_list);
}
void	chunk_based_sort(t_list **a_lst, t_list **b_lst)
{
	t_list	*lst;
	int		count;
	int		i;
	int		r;
	int		rotate_count;

	i = 0;
	count = lst_count(*a_lst);
	r = root(count);
	while (i <= r)
	{
		lst = *a_lst;
		while (lst)
		{
			if (i * r <= lst->rank && lst->rank < (i + 1) * r)
				pb(a_lst);
			lst = lst->next;
		}
		i++;
	}
	while (count >= 0)
	{
		rotate_count = 0;
		lst = *a_lst;
		while (lst->next != NULL)
		{
			if(count == lst->rank)
				break;
			rotate_count++;
		}
		call_rotate_push(a_lst,b_lst,rotate_count);
		call_reverse(a_lst,b_lst,rotate_count);
	}
	while(b_lst)
}
