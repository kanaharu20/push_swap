/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyonaha <kyonaha@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 11:10:55 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 15:26:17 by kyonaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

float	disorder(t_list **a_lst)
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
	return (((float)mistakes / total_pairs));
}
