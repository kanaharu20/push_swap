/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hkanamit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:53:10 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/13 22:00:29 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
t_list	*make_a_node(t_list *a_node, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		ft_lstadd_back(&a_node, ft_lstnew(argv[i]));
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
			write(1, "Error\n", 6);
			return (0);
		}
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				write(1, "Error\n", 6);
				return (0);
			}
			j++;
		}
	}
	return (1);
}

int	strlen_original(char *num)
{
	int	sign;
	int	len;
	int	idx;

	sign = 1;
	len = 0;
	idx = 0;
	if (num[idx] == '-' || num[idx] == '+')
	{
		if (num[idx] == '-')
			sign = -1;
		idx++;
	}
	while (num[idx])
	{
		idx++;
		len++;
	}
	return (len * sign);
}

int	strcmp_original2(char *str)
{
}
int	strcmp_original(t_list *a)
{
	char	*a_num;
	char	*b_num;
	t_list	*next;
	int		len_a;
	int		len_b;

	next = a->next;
	a_num = a->content;
	b_num = next->content;
	len_a = strlen_original(a_num);
	len_b = strlen_original(b_num);
	if (len_a < len_b)
		return (0);
	else if (len_a > len_b)
		return (1);
	strcmp_original2(a_num);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_list	*a_node;
	t_list	*b_node;

	a_node = NULL;
	b_node = NULL;
	if (error_handle(argc, argv) == 0)
		return (0);
	a_node = make_a_node(a_node, argc, argv);
}
