/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:20:52 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/19 15:20:29 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
void small_sort(t_list *a_lst ,t_data *bench_data)
{
	int x = a_lst->content;
	int y = a_lst->content;
	
}
int	base_sort(t_list *a_lst, t_data *bench_data)
{
	int	count;

	count = lst_count(a_lst);
	if (count == 1)
		return (1);
	else if (count == 2)
	{
		if (a_lst->rank > a_lst->next->content)
			sa(&a_lst, bench_data);
		return (1);
	}
	else if (count == 3)
		small_sort()
}
