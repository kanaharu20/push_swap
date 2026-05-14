# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkanamit <hkanamit@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/14 17:28:12 by hkanamit          #+#    #+#              #
#    Updated: 2026/05/14 17:31:14 by hkanamit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap.a

SOURCE =

OBJECT = $(SOURCE : .c = .o)

CC = cc
CFLAG = -Wall -Werror -Wextra

all : $(NAME)

$(NAME):$(OBJECT)
	ar rcs

$()