/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 11:00:20 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 17:04:32 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(lst);
		current = next;
	}
	*lst = NULL;
	return ;
}

t_list	*ft_lstnew(int content)
{
	t_list	*node_new;

	node_new = NULL;
	node_new = malloc(sizeof(t_list));
	if (node_new == NULL)
		return (NULL);
	node_new->content = content;
	node_new->next = NULL;
	return (node_new);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}
