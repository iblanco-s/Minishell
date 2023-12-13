# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inigo <inigo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 16:41:26 by iblanco-          #+#    #+#              #
#    Updated: 2023/12/13 19:12:45 by inigo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -Wall -Werror -Wextra

RM = rm -f

SRCS = builtin/tester_main.c \
	   builtin/ft_echo.c \
	   builtin/ft_pwd.c \
	   builtin/ft_env.c \
	   builtin/ft_unset.c \
	   builtin/ft_export.c \
	   builtin/utils_1.c \
	   builtin/utils_2.c \
	   #builtin/ft_cd.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

limpito: all clean

re:	fclean all

.PHONY:	all clean fclean re