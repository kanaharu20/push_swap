/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 16:36:17 by hkanamit          #+#    #+#             */
/*   Updated: 2026/05/17 12:13:50 by hkanamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				content;
	struct s_list	*next;
	int				rank;
}					t_list;

typedef struct s_data
{
	int				sa_cnt;
	int				sb_cnt;
	int				ss_cnt;
	int				pa_cnt;
	int				pb_cnt;
	int				ra_cnt;
	int				rb_cnt;
	int				rr_cnt;
	int				rra_cnt;
	int				rrb_cnt;
	int				rrr_cnt;
	int				dis;
	int				flag;
}					t_data;

int					atoi_original(const char *nptr, int *err_flag);
int					detect_duplicate_values(t_list *lst, int a);
void				ft_lstclear(t_list **lst);
t_list				*ft_lstnew(int content);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_isdigit(int c);
int					error_handle(int argc, char *argv[]);
int					strcmp_original(char *s1, char *s2);
int					call_algo(char **argv, int *bench_flag);
void				bench_mark(t_data bench_mark);
void				push(t_list **to, t_list **from);
void				pa(t_list **a_lst, t_list **b_lst, t_data *bench_data);
void				pb(t_list **a_lst, t_list **b_lst, t_data *bench_data);
void				swap(t_list **node_ptr);
void				sa(t_list **a_node, t_data *bench_data);
void				sb(t_list **b_node, t_data *bench_data);
void				ss(t_list **a_node, t_list **b_node, t_data *bench_data);
void				ra(t_list **a_lst, t_data *bench_data);
void				rb(t_list **b_lst, t_data *bench_data);
void				rr(t_list **a_lst, t_list **b_lst, t_data *bench_data);
void				rra(t_list **a_lst, t_data *bench_data);
void				rrb(t_list **b_lst, t_data *bench_data);
void				rrr(t_list **a_lst, t_list **b_lst, t_data *bench_data);
void				make_rank(t_list **a_lst);
void				buble_sort(t_list **a_lst, t_list **b_lst,
						t_data *bench_data);
int					lst_count(t_list *lst);
void				chunk_based_sort2(t_list **a_lst, t_list **b_lst, int count,
						t_data *bench_data);
void				chunk_based_sort(t_list **a_lst, t_list **b_lst,
						t_data *bench_data);
void				lsd_sort(t_list **a_lst, t_list **b_lst,
						t_data *bench_data);
int					judge(t_list **a_lst, t_list **b_lst);
float				disorder(t_list **a_lst, t_data *bench_data);
void				put_char(char c, int *ret);
void				putstr(char *s, int *ret);
void				put_nbr_2(int nbr, int *ret);
void				put_nbr3(int nbr, int *ret);
void				put_nbr(int nbr, int *ret);
void				put_unsigned_nbr_base(unsigned int nbr, char *base,
						int *ret);
void				put_address(unsigned long long nbr, char *base, int *ret,
						int flag);
void				put_per_something(const char format, int *ret);
void				output_count(const char format, va_list args, int *ret);
int					ft_printf(const char *format, ...);
void				put_address_2(int *ret);

#endif