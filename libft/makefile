# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 17:41:17 by iblanco-          #+#    #+#              #
#    Updated: 2022/10/03 16:55:19 by iblanco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = ft_strlcat.c  ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_striteri.c ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c ft_strdup.c ft_substr.c ft_strjoin.c ft_calloc.c ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strchr.c ft_memmove.c ft_memcpy.c ft_bzero.c ft_memset.c ft_strnstr.c ft_strncmp.c ft_toupper.c ft_tolower.c  ft_strlen.c ft_strlcpy.c ft_isprint.c ft_isdigit.c ft_isascii.c ft_isalpha.c ft_isalnum.c ft_atoi.c 

OBJS = $(SRCS:.c=.o)

BONUS = ft_lstnew.c ft_lstmap.c ft_lstclear.c ft_lstiter.c ft_lstdelone.c ft_lstlast.c ft_lstsize.c ft_lstadd_front.c ft_lstadd_back.c

BONUS_OBJS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	
bonus:	$(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean:	clean
	$(RM) $(NAME)
	
re:	fclean $(NAME)

.PHONY:	all clean fclean re bonus

