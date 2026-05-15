/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 11:10:55 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 15:44:57 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

float	disorder(t_list **a_lst,t_data *bench_data)
{
	float	mistakes;
	float	total_pairs;
	t_list	*tmp;

	mistakes = 0;
	total_pairs = 0;
	tmp = *a_lst;
	while (tmp->next != NULL)
	{
		if (tmp->content > tmp->next->content)
			mistakes++;
		total_pairs++;
		tmp = tmp->next;
	}
	bench_data->dis = ((float)mistakes/total_pairs);
	return (((float)mistakes / total_pairs));
}
