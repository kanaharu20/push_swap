/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 10:57:04 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 17:03:24 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	lst_count(t_list *lst)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
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
		if (j == 0 && (argv[i][j] == '-' || argv[i][j] == '+'))
			j++;
		if (argv[i][j] == '\0')
		{
			write(2, "Error\n", 6);
			return (0);
		}
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

int	detect_duplicate_values(t_list *lst, int a)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->content == a)
			return (-1);
		tmp = tmp->next;
	}
	return (1);
}

