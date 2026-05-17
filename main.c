/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:53:10 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/17 16:16:24 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_list	*make_a_lst(t_list **a_lst, int argc, char *argv[])
{
	int		i;
	int		err_flag;
	t_list	*tmp;

	i = 1;
	while (i < argc)
	{
		err_flag = 0;
		tmp = ft_lstnew(atoi_original(argv[i], &err_flag));
		if (!tmp || err_flag == -1 || detect_duplicate_values(*a_lst,
				tmp->content) == -1)
		{
			free(tmp);
			ft_lstclear(a_lst);
			write(2, "Error\n", 6);
			return (NULL);
		}
		ft_lstadd_back(a_lst, tmp);
		i++;
	}
	return (*a_lst);
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
}

int	main(int argc, char *argv[])
{
	t_data	bench_data;
	t_list	*a_lst;
	t_list	*b_lst;
	int		bench_flag;

	a_lst = NULL;
	b_lst = NULL;
	reset(&bench_data);
	if (argc < 2)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	bench_flag = judge_bench_flag(argv);
	bench_data.flag = call_algo(argv, bench_flag);
	if (bench_flag == 1)
	{
		argv++;
		argc--;
	}
	if (bench_data.flag != 0)
	{
		argv++;
		argc--;
	}
	if (error_handle(argc, argv) == 0)
		return (1);
	a_lst = make_a_lst(&a_lst, argc, argv);
	if (!a_lst)
		return (1);
	make_rank(&a_lst);
	bench_data.dis = disorder(&a_lst, &bench_data);
	if (bench_data.flag == 1 || ((bench_data.flag == 0 || bench_data.flag == 4)
			&& bench_data.dis < 2000))
		buble_sort(&a_lst, &b_lst, &bench_data);
	else if (bench_data.flag == 2 || ((bench_data.flag == 0
				|| bench_data.flag == 4) && bench_data.dis < 5000))
		chunk_based_sort(&a_lst, &b_lst, &bench_data);
	else if (bench_data.flag == 3 || (bench_data.flag == 0
			|| bench_data.flag == 4))
		lsd_sort(&a_lst, &b_lst, &bench_data);
	if (bench_flag == 1)
		bench_mark(bench_data);
	ft_lstclear(&a_lst);
	return (0);
}
