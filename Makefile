# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/14 17:28:12 by hkanamit          #+#    #+#              #
#    Updated: 2026/05/15 11:06:23 by hkanamit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap.a

SOURCE = atoi.c buble_sort.c chunk_base_sort.c \
		helper_func.c judge.c list.c lsd_sort.c main.c\
		push.c rank.c reverese_rotate.c rotate.c swap.c

OBJECT = $(SOURCE :.c=.o)

CC = cc
CFLAG = -Wall -Werror -Wextra

all : $(NAME)

$(NAME):$(OBJECT)
	ar rcs $(NAME) $(OBJECT)

%.o:%.c
	$(CC) $(CFLAG) -I . -o $< -c $@

clean :
	rm -f $(OBJECT)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY clean fclean re all