/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 11:10:55 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 12:27:39 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	disorder(t_list **a_lst)
{
	float	mistakes;
	float	total_pairs;
	t_list	*tmp;

	mistakes = 0;
	total_pairs = 0;
	tmp = *a_lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		if (tmp->content > tmp->next->content)
			mistakes++;
		total_pairs++;
	}
	return ((float)(mistakes / total_pairs));
}
