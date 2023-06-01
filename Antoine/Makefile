# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 15:03:29 by anvincen          #+#    #+#              #
#    Updated: 2023/06/01 16:34:29 by anvincen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#antoine/Makefile
SRC =	main.c ft_error.c ft_command.c ft_get_command.c quotes.c\
		change_directory.c echo.c export.c export_utils.c env.c free.c list.c\

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
