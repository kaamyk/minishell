# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoine <antoine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 17:59:08 by xuluu             #+#    #+#              #
#    Updated: 2023/07/20 14:07:41 by antoine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c \
		n_export.c n_environment.c n_environment_utils.c list.c free.c utils.c\
		env.c n_unset.c ft_cd.c pwd.c\

OBJ = $(SRC:.c=.o)

NAME = minishell

CC = gcc

READLINE = -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include

CFLAGS =  -Wall -Wextra -Werror -g3

LIBFTPATH = ../libft

LIBFTS = $(LIBFTPATH)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(RM) file*
	@$(MAKE) -sC $(LIBFTPATH)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFTS) $(READLINE) -o $(NAME)

$(OBJ): %.o: %.c Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

n:
	cp -rf *.c *.h Makefile ok2

clean:
	@$(MAKE) clean -sC $(LIBFTPATH)
	@$(RM) $(OBJ)

fclean: clean
	@$(MAKE) fclean -sC $(LIBFTPATH)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
