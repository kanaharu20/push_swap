/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyonaha <kyonaha@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 16:36:17 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/15 16:01:31 by kyonaha          ###   ########.fr       */
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

typedef struct s_data
{
	size_t			total;
	size_t			sa_cnt;
	size_t			sb_cnt;
	size_t			ss_cnt;
	size_t			pa_cnt;
	size_t			pb_cnt;
	size_t			ra_cnt;
	size_t			rb_cnt;
	size_t			rr_cnt;
	size_t			rra_cnt;
	size_t			rrb_cnt;
	size_t			rrr_cnt;
	float			dis;
	int				flag;
}					t_data;

/* atoi_hkanamit.c */
int					atoi_original(const char *nptr, int *err_flag);

/* main_hkanamit.c */
int					detect_duplicate_values(t_list *lst, int a);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void delete (void *content);
void				ft_lstclear(t_list **lst, void (*del)(void *));
t_list				*ft_lstnew(int content);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_isdigit(int c);
int					error_handle(int argc, char *argv[]);

/* push.c */
void				push(t_list **to, t_list **from);
void				pa(t_list **a_lst, t_list **b_lst, t_data *bench_data);
void				pb(t_list **a_lst, t_list **b_lst, t_data *bench_data);

/* swap.c */
void				swap(t_list **node_ptr);
void				sa(t_list **a_node, t_data *bench_data);
void				sb(t_list **b_node, t_data *bench_data);
void				ss(t_list **a_node, t_list **b_node, t_data *bench_data);

/* rotate.c */
void				ra(t_list **a_lst, t_data *bench_data);
void				rb(t_list **b_lst, t_data *bench_data);
void				rr(t_list **a_lst, t_list **b_lst, t_data *bench_data);

/* reverse_rotate.c */
void				rra(t_list **a_lst, t_data *bench_data);
void				rrb(t_list **b_lst, t_data *bench_data);
void				rrr(t_list **a_lst, t_list **b_lst, t_data *bench_data);

/* rank.c */
void				make_rank(t_list **a_lst);

/* buble_sort.c */
void				buble_sort(t_list **a_lst, t_list **b_lst,
						t_data *bench_data);

/* chunk_based_sort.c */
int					lst_count(t_list *lst);
void				chunk_based_sort2(t_list **a_lst, t_list **b_lst,
						int count, t_data *bench_data);
void				chunk_based_sort(t_list **a_lst, t_list **b_lst,
						t_data *bench_data);

/* lsd_sort.c */
void				lsd_sort(t_list **a_lst, t_list **b_lst,
						t_data *bench_data);

/* judge.c */
int					judge(t_list **a_lst, t_list **b_lst);

/* disorder.c */
float				disorder(t_list **a_lst, t_data *bench_data);

#endif