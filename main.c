/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:53:10 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 11:26:10 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
