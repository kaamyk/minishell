# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 11:33:25 by xuluu             #+#    #+#              #
#    Updated: 2023/05/23 17:20:44 by anvincen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SRC =	ft_atoi.c \
# 		ft_bzero.c \
# 		ft_calloc.c \
# 		ft_isdigit.c \
# 		ft_putchar_fd.c \
# 		ft_putnbr_fd.c \
# 		ft_putstr_fd.c \
# 		ft_split.c \
# 		ft_strchr.c \
# 		ft_strjoin.c \
# 		ft_strlen.c \
# 		ft_strncmp.c \
# 		ft_itoa.c \
# 		ft_strdup.c

SRC =	ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strchr.c \
		ft_split.c \
		ft_strrchr.c \
		ft_memset.c

OBJ = $(SRC:.c=.o)

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

all : $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

$(OBJ): %.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
