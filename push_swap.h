/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 16:36:17 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/14 16:39:03 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				content;
	struct s_list	*next;
	unsigned int	rank;
}					t_list;

/* atoi_hkanamit.c */
int		atoi_original(const char *nptr, int *err_flag);

/* main_hkanamit.c */
int		detect_duplicate_values(t_list *lst, int a);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	delete(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*make_a_lst(t_list **a_lst, int argc, char *argv[]);
int		ft_isdigit(int c);
int		error_handle(int argc, char *argv[]);

/* push.c */
void	push(t_list **to, t_list **from);
void	pa(t_list **a_lst, t_list **b_lst);
void	pb(t_list **a_lst, t_list **b_lst);

/* swap.c */
void	swap(t_list **node_ptr);
void	sa(t_list **a_node);
void	sb(t_list **b_node);
void	ss(t_list **a_node, t_list **b_node);

/* rotate.c */
void	ra(t_list **a_lst);
void	rb(t_list **b_lst);
void	rr(t_list **a_lst, t_list **b_lst);

/* reverse_rotate.c */
void	rra(t_list **a_lst);
void	rrb(t_list **b_lst);
void	rrr(t_list **a_lst, t_list **b_lst);

/* rank.c */
void	make_rank(t_list **a_lst);

/* buble_sort.c */
void	buble_sort(t_list **a_lst, t_list **b_lst);

/* chunk_based_sort.c */
int		lst_count(t_list *lst);
int		root(int lst_count);
void	call_rotate_push(t_list **a_lst, t_list **b_lst, int rotate_count);
void	chunk_based_sort(t_list **a_lst, t_list **b_lst);

#endif