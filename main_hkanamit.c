/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hkanamit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:53:10 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 11:01:07 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
