# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 17:59:08 by xuluu             #+#    #+#              #
#    Updated: 2023/05/23 17:23:39 by anvincen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c \
		ft_get_command.c \
		ft_command.c \
		ft_error.c\
		signal.c

OBJ = $(SRC:.c=.o)

NAME = minishell

CC = cc

READLINE = -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include

CFLAGS =  -Wall -Wextra -Werror -g3

LIBFTPATH = ./libft

LIBFTS = $(LIBFTPATH)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(MAKE) -sC $(LIBFTPATH)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFTS) $(READLINE) -o $(NAME)

$(OBJ): %.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) clean -sC ./libft
	$(RM) $(OBJ)

fclean: clean
	@$(MAKE) fclean -sC ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
