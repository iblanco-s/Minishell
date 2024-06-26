# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 16:41:26 by iblanco-          #+#    #+#              #
#    Updated: 2024/04/30 18:27:33 by jsalaber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -Wall -Werror -Wextra #-fsanitize=address -g3

RM = rm -f

SRCS = builtin/ft_echo.c \
	   builtin/ft_pwd.c \
	   builtin/ft_env.c \
	   builtin/ft_unset.c \
	   builtin/ft_export.c \
	   builtin/ft_isbuiltin.c \
	   builtin/ft_exit.c \
	   builtin/utils_1.c \
	   builtin/utils_2.c \
	   builtin/ft_cd.c \
	   builtin/ft_cd_aux.c \
	   initiation/main.c \
	   initiation/obtain_env.c \
	   initiation/setup.c \
	   initiation/free.c \
	   parse/initial_check.c \
	   parse/aux_initial_check.c \
	   parse/general_split.c \
	   parse/split_special_chars.c \
	   parse/group_by_pipes.c \
	   parse/expand_dollar_utils.c \
	   parse/expand_dollar.c \
	   parse/parse_utils.c \
	   parse/aux_group_by_pipes.c \
	   parse/aux_reddirections.c \
	   exec/open_files.c \
	   exec/files.c \
	   exec/pipe.c \
	   exec/exec.c \
	   exec/utils.c \
	   signal/signals.c \

OBJS = $(SRCS:.c=.o)

LIBFT = libft
LIBFT_A = $(LIBFT)/libft.a

all: $(NAME)

$(LIBFT_A):
	make bonus -C $(LIBFT)

%.o: %.c
	$(CC) -I/usr/local/opt/readline/include -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(OBJS) -L$(LIBFT) -lft -lreadline -L/usr/local/opt/readline/lib -o $(NAME)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT) clean

fclean:	clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean

limpito: all clean

re:	fclean all

.PHONY:	all clean fclean re