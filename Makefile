# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/14 17:28:12 by hkanamit          #+#    #+#              #
#    Updated: 2026/05/15 10:55:57 by hkanamit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap.a

SOURCE = 

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