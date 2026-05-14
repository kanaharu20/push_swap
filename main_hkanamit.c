/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hkanamit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:53:10 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/14 14:09:30 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	cmp(int former, int latter)
{
	if (former < latter)
		return (1);
	return (0);
}
int	detect_duplicate_values(t_list *lst, int a)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->content = a)
			return (-1);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

void delete (void *content)
{
	(void)(*content);
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

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	error_handle(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		if (j == 0 && argv[i][j] == '-')
			j++;
		if (argv[i][j] == '0' && argv[i][j + 1] != '\0')
		{
			write(2, "Error\n", 6);
			return (0);
		}
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				write(2, "Error\n", 6);
				return (0);
			}
			j++;
		}
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_list	*a_lst;
	t_list	*b_lst;

	a_lst = NULL;
	b_lst = NULL;
	if (error_handle(argc, argv) == 0)
		return (0);
	a_lst = make_a_lst(a_lst, argc, argv);
}
