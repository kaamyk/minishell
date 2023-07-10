# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 17:59:08 by xuluu             #+#    #+#              #
#    Updated: 2023/05/26 10:52:59 by anvincen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	pipex.c \
		pipex2.c \
		pipex3.c

OBJ = $(SRC:.c=.o)

NAME = minishell

CC = cc

CFLAGS =  -Wall -Wextra -Werror -g3

LIBFTPATH = ./libft

LIBFTS = $(LIBFTPATH)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(MAKE) -sC $(LIBFTPATH)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFTS) -o $(NAME)

	@$(MAKE) clean -sC ./libft
	@$(RM) $(OBJ)

$(OBJ): %.o: %.c Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

n:
	cp -rf *.c *.h Makefile ok

clean:
	@$(MAKE) clean -sC ./libft
	@$(RM) $(OBJ)

fclean: clean
	@$(MAKE) fclean -sC ./libft
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
