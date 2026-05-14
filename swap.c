/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 16:18:02 by kyonaha           #+#    #+#             */
/*   Updated: 2026/05/14 14:02:55 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_list **node_ptr) {
  t_list *node;
  t_list *next;

  node = *node_ptr;
  if (node != NULL && node->next != NULL) {
    next = node->next;
    node->next = next->next;
    next->next = node;
    *node_ptr = next;
  }
}

void	sa(t_list **a_lst) {
  swap(a_lst);
  write(1, "sa\n", 3);
}

void	sb(t_list **b_lst) {
  swap(b_lst);
  write(1, "sb\n", 3);
}

void	ss(t_list **a_lst, t_list **b_lst) {
  swap(a_lst);
  swap(b_lst);
  write(1, "ss\n", 3);
}
