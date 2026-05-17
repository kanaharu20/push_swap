# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/14 17:28:12 by hkanamit          #+#    #+#              #
#    Updated: 2026/05/15 17:12:08 by hkanamit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

SOURCE = atoi.c bench_mark.c buble_sort.c call_algo.c chunk_based_sort.c \
		disorder.c ft_printf.c ft_printf2.c ft_printf3.c helper_func.c \
		judge.c list.c lsd_sort.c main.c push.c rank.c \
		reverse_rotate.c rotate.c swap.c

OBJECT = $(SOURCE:.c=.o)

CC = cc
CFLAG = -Wall -Werror -Wextra

all : $(NAME)

$(NAME):$(OBJECT)
	$(CC) $(CFLAG) -o $(NAME) $(OBJECT)

%.o:%.c
	$(CC) $(CFLAG) -I . -c $< -o $@

clean :
	rm -f $(OBJECT)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean re all