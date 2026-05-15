/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 12:14:03 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 12:58:16 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	call_algo(char *argv[])
{
	int	flag;

	flag = 0;
	if (argv[1] == "--simple")
		flag = 1;
	else if (argv[1] == "--medium")
		flag = 2;
	else if (argv[1] == "--complex")
		flag = 3;
	else if (argv[1] == "--adaptive")
		flag = 4;

	if (flag != 0)
		argv++;
	else
		flag = 4;
	return (flag);
}
