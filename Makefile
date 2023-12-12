# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 16:41:26 by iblanco-          #+#    #+#              #
#    Updated: 2023/12/12 18:43:08 by iblanco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -Wall -Werror -Wextra

RM = rm -f

SRCS = main.c \
       builtin/ft_cd.c \
       builtin/tester_main.c \
       utils/utils_1.c \
	   utils/utils_2.c \
	   builtin/ft_pwd.c \
	   builtin/ft_env.c \
	   builtin/ft_unset.c \
	   builtin/ft_export.c \

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