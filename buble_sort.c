/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buble_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyonaha <kyonaha@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 13:43:24 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/14 15:12:08 by kyonaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	cmp(int former, int latter)
{
	if (former < latter)
		return (1);
	return (0);
}

void	buble_sort(t_list **a_lst, t_list **b_lst)
{
	t_list	*lst;
	size_t	i;
	size_t	cnt_lst;

	lst = *a_lst;
	cnt_lst = 0;
	while (lst->next != NULL)
	{
		lst = lst->next;
		cnt_lst++;
	}
	while (cnt_lst)
	{
		i = 0;
		while (++i <= cnt_lst)
		{
			if (cmp((*a_lst)->content, (*a_lst)->next->content))
				sa(a_lst);
			ra(a_lst);
		}
		pb(a_lst, b_lst);
		cnt_lst--;
	}
	while (*b_lst != NULL)
		pa(a_lst, b_lst);
}
