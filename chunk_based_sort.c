/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_based_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 15:32:44 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/14 15:44:27 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	chunk_based_sort(t_list **a_lst,t_list **b_lst)
{
	t_list *lst = *a_lst;
	int lst_count = 0;
	int i = 0;
	while(lst->next != NULL)
	{
		lst_count++;
		lst = lst->next;
	}

	while(i < lst_count)
	{
		
	}




}