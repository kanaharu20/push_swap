/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 11:00:20 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 11:01:54 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		ft_lstdelone(current, del);
		current = next;
	}
	*lst = NULL;
	return ;
}

t_list	*ft_lstnew(void *content)
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

t_list	*make_a_lst(t_list **a_lst, int argc, char *argv[])
{
	int		i;
	int		err_flag;
	int		tmp;
	t_list	**first;

	tmp = 0;
	first = a_lst;
	err_flag = 0;
	i = 1;
	while (i < argc)
	{
		tmp = ft_lstnew(atoi_original(argv[i], &err_flag));
		ft_lstadd_back(&a_lst, tmp);
		if (err_flag == -1 || detect_duplicate_values(*first, tmp) == -1)
		{
			write(2, "Error\n", 6);
			return (NULL);
		}
		i++;
	}
}
