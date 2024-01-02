# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 16:41:26 by iblanco-          #+#    #+#              #
#    Updated: 2024/01/02 18:31:36 by iblanco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -Wall -Werror -Wextra -fsanitize=address -g3

RM = rm -f

SRCS = builtin/tester_main.c \
	   builtin/ft_echo.c \
	   builtin/ft_pwd.c \
	   builtin/ft_env.c \
	   builtin/ft_unset.c \
	   builtin/ft_export.c \
	   builtin/ft_exit.c \
	   builtin/utils_1.c \
	   builtin/utils_2.c \
	   builtin/ft_cd.c \
	   builtin/ft_cd_aux.c \

OBJS = $(SRCS:.c=.o)

LIBFT = libft

all: $(NAME) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L$(LIBFT) -lft -o $(NAME)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT) clean

fclean:	clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean

limpito: all clean

re:	fclean all

.PHONY:	all clean fclean re $(LIBFT)