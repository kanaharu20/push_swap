/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:53:10 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 15:59:13 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_list	**make_a_lst(t_list **a_lst, int argc, char *argv[])
{
	int		i;
	int		err_flag;
	t_list	*tmp;
	t_list	**first;

	tmp = 0;
	first = a_lst;
	err_flag = 0;
	i = 1;
	while (i < argc)
	{
		tmp = ft_lstnew(atoi_original(argv[i], &err_flag));
		ft_lstadd_back(a_lst, tmp);
		if (err_flag == -1 || detect_duplicate_values(*first, tmp->content) ==
			-1)
		{
			write(2, "Error\n", 6);
			return (NULL);
		}
		i++;
	}
	return (a_lst);
}

int	strcmp_original(char *s1, char *s2)
{
	int	idx;

	idx = 0;
	while (s2[idx] && s1[idx] == s2[idx])
		idx++;
	if (s1[idx] == s2[idx])
		return (1);
	return (0);
}

static int	call_algo(char *argv[])
{
	int	flag;

	flag = 0;
	if (strcmp_original(argv[1], "--simple"))
		flag = 1;
	else if (strcmp_original(argv[1], "--medium"))
		flag = 2;
	else if (strcmp_original(argv[1], "--complex"))
		flag = 3;
	else if (strcmp_original(argv[1], "--adaptive"))
		flag = 4;
	if (flag != 0)
		argv++;
	else
		flag = 4;
	return (flag);
}
void	reset(t_data *bench_data)
{
	bench_data->dis = 0;
	bench_data->flag = 0;
	bench_data->pa_cnt = 0;
	bench_data->pb_cnt = 0;
	bench_data->ra_cnt = 0;
	bench_data->rb_cnt = 0;
	bench_data->rr_cnt = 0;
	bench_data->rra_cnt = 0;
	bench_data->rrb_cnt = 0;
	bench_data->rrr_cnt = 0;
	bench_data->sa_cnt = 0;
	bench_data->sb_cnt = 0;
	bench_data->ss_cnt = 0;
	bench_data->total = 0;
}

int	main(int argc, char *argv[])
{
	t_data	*bench_data;
	t_list	**a_lst;
	t_list	**b_lst;
	int		flag;
	float	dis;

	reset(bench_data);
	*a_lst = NULL;
	b_lst = NULL;
	if (error_handle(argc, argv) == 0)
		return (0);
	flag = call_algo(argv);
	a_lst = make_a_lst(a_lst, argc, argv);
	dis = disorder(a_lst);
	if (flag == 1 || (flag == 4 && dis < 0.2))
		buble_sort(a_lst, b_lst, bench_data);
	else if (flag == 2 || (flag == 4 && dis < 0.5))
		chunk_based_sort(a_lst, b_lst, bench_data);
	else if (flag == 3 || flag == 4)
		lsd_sort(a_lst, b_lst, bench_data);
	return (0);
}
