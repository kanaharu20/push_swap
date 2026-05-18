/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsd_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyonaha <kyonaha@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:57:10 by kyonaha           #+#    #+#             */
/*   Updated: 2026/05/17 17:54:47 by kyonaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	bit_length(int size)
{
	int	bits;

	bits = 0;
	while ((1 << bits) < size)
		bits++;
	return (bits);
}

void	lsd_sort(t_list **a_lst, t_list **b_lst, t_data *bench_data)
{
	int	bits;
	int	bit;
	int	b_count;
	int	i;
	int	size;

	size = lst_count(*a_lst);
	bits = bit_length(size);
	bit = 0;
	while (bit < bits)
	{
		b_count = 0;
		i = 0;
		while (i < size)
		{
			if (((*a_lst)->rank >> bit) & 1)
				ra(a_lst, bench_data);
			else
			{
				pb(a_lst, b_lst, bench_data);
				b_count++;
			}
			i++;
		}
		while (b_count-- > 0)
			pa(a_lst, b_lst, bench_data);
		bit++;
	}
}
