/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_mark.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 10:35:05 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/17 11:34:47 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	write_strategy(t_data bench_data)
{
	if (bench_data.flag == 1 || ((bench_data.flag == 0 || bench_data.flag == 4)
			&& bench_data.dis < 0.2))
		write(1, "Simple / O(n²)\n", 16);
	else if (bench_data.flag == 2 || ((bench_data.flag == 0
				|| bench_data.flag == 4) && bench_data.dis < 0.5))
		write(1, "Adaptive / O(n√n)\n", 18);
	else if (bench_data.flag == 3 || (bench_data.flag == 0
			|| bench_data.flag == 4))
		write(1, "Complex / O(n log n)\n", 21);
}
void	bench_mark(t_data bench_data)
{
	int total = bench_data.pa_cnt + bench_data.pb_cnt + bench_data.ra_cnt
		+ bench_data.rb_cnt + bench_data.rr_cnt + bench_data.rra_cnt
		+ bench_data.rrb_cnt + bench_data.rrr_cnt + bench_data.sa_cnt
		+ bench_data.sb_cnt + bench_data.ss_cnt;
	ft_printf("[bench] disorder:  %f%%", bench_data.dis); //%f の追加が必要
	ft_printf("[bench] strategy:  ");
	write_strategy(bench_data);
	ft_printf("[bench] total_ops: %d\n", total);
	ft_printf("[bench] sa: %d  sb: %d  ss: %d  pa: %d  pb: %d\n",
		bench_data.sa_cnt, bench_data.sb_cnt, bench_data.ss_cnt,
		bench_data.pa_cnt, bench_data.pb_cnt);
	ft_printf("[bench] ra: %d  rb: %d  rr: %d  rra: %d  rrb: %d  rrr: %d\n",
		bench_data.ra_cnt, bench_data.rb_cnt, bench_data.rr_cnt,
		bench_data.rra_cnt, bench_data.rrb_cnt, bench_data.rrr_cnt);
	
}