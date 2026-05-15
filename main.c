/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyonaha <kyonaha@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:53:10 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 15:04:53 by kyonaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_list	**make_a_lst(t_list **a_lst, int argc, char *argv[])
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
		ft_lstadd_back(a_lst, tmp);
		if (err_flag == -1 ||
			detect_duplicate_values(*first, tmp) == -1)
		{
			write(2, "Error\n", 6);
			return (NULL);
		}
		i++;
	}
	return (a_lst);
}

int	strcmp(char *s1, char *s2)
{
	int	idx;

	idx = 0;
	while (s2[idx] && s1[idx] == s2[idx])
		idx++;
	if (s1[idx] == '\0')
		return (1);
	return (0);
}

static int	call_algo(char *argv[])
{
	int	flag;

	flag = 0;
	if (strcmp(argv[1],"--simple"))
		flag = 1;
	else if (strcmp(argv[1], "--medium"))
		flag = 2;
	else if (strcmp(argv[1], "--complex"))
		flag = 3;
	else if (strcmp(argv[1], "--adaptive"))
		flag = 4;
	if (flag != 0)
		argv++;
	else
		flag = 4;
	return (flag);
}

int	main(int argc, char *argv[])
{
	t_list	**a_lst;
	t_list	**b_lst;
	int		flag;
	float	dis;

	a_lst = NULL;
	b_lst = NULL;
	if (error_handle(argc, argv) == 0)
		return (0);
	flag = call_algo(argv);
	a_lst = make_a_lst(a_lst, argc, argv);
	dis = disorder(a_lst);
	if (flag == 1 || (flag == 4 && dis < 0.2))
		buble_sort(a_lst, b_lst);
	else if (flag == 2 || (flag == 4 && dis < 0.5))
		chunk_based_sort(a_lst, b_lst);
	else if (flag == 3 || flag == 4)
		lsd_sort(a_lst, b_lst);
	return (0);
}
