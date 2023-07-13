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

SRC =	main.c \
		ft_utile/ft_titre.c \
		ft_utile/ft_error.c \
		ft_utile/ft_delete_space.c \
		ft_check_syntaxe/ft_check_syntaxe.c \
		ft_check_syntaxe/ft_check_syntaxe2.c \
		ft_check_syntaxe/ft_check_syntaxe3.c \
		ft_split_mn/ft_split_mn.c \
		ft_redirection/ft_redirection.c \
		ft_redirection/ft_redirection2.c \
		ft_redirection/ft_redirection3.c \
		ft_antoine/signal.c \
		ft_antoine/utils.c \
		ft_antoine/export.c \
		ft_antoine/free.c \
		ft_antoine/environment.c \
		ft_antoine/environment_utils.c \
		ft_antoine/list.c \
		ft_antoine/env.c \
		ft_antoine/echo.c \
		ft_antoine/unset.c \
		ft_antoine/ft_cd.c \
		ft_antoine/exit.c \
		ft_parsing/ft_parsing.c \
		ft_parsing/ft_parsing2.c \
		ft_parsing/ft_parsing3.c \
		ft_parsing/ft_parsing4.c \
		ft_parsing/ft_parsing5.c \
		ft_parsing/ft_parsing6.c \
		ft_parsing/ft_parsing7.c \
		ft_parsing/ft_parsing8.c \
		ft_utile/ft_utile.c \
		ft_utile/ft_utile2.c \
		ft_execute.c \
		ft_get_cmd.c \
		ft_buitins.c \
		ft_other_cmd.c \
		pipex.c \

OBJ = $(SRC:.c=.o)

NAME = minishell

CC = gcc

READLINE = -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include

CFLAGS =  -Wall -Wextra -Werror -g3

LIBFTPATH = ./libft

LIBFTS = $(LIBFTPATH)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(RM) file*
	@$(MAKE) -sC $(LIBFTPATH)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFTS) $(READLINE) -o $(NAME)

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
