# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 17:59:08 by xuluu             #+#    #+#              #
#    Updated: 2023/06/20 16:54:50 by anvincen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c \
		signal.c \
		ft_delete_space.c \
		ft_error.c \
		ft_quotes.c \
		ft_check_syntaxe.c \
		ft_execute.c \
		ft_split_mn.c \
		ft_split_mn2.c \
		ft_split_cmd.c \
		ft_split_cmd2.c \
		ft_split_cmd3.c \
		ft_split_cmd4.c \
		ft_split_cmd5.c \
		ft_get_cmd.c \
		ft_classify_str.c \
		ft_redirection.c \
		ft_redirection2.c \
		ft_redirection4.c \
		utils.c \
		export.c \
		free.c \
		environment.c \
		environment_utils.c \
		list.c \
		env.c \
		echo.c \
		unset.c \
		ft_cd.c \
		join_print.c \
		ft_other_cmd.c \

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

n:
	cp -rf *.c *.h Makefile ok

clean:
	@$(MAKE) clean -sC ./libft
	$(RM) $(OBJ)

fclean: clean
	@$(MAKE) fclean -sC ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
