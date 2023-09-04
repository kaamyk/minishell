# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoine <antoine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 17:59:08 by xuluu             #+#    #+#              #
#    Updated: 2023/08/30 14:48:13 by antoine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c \
		ft_utiles/ft_titre.c \
		ft_utiles/ft_delete_space.c \
		ft_utiles/ft_delete_quotes.c \
		ft_utiles/ft_error.c \
		ft_utiles/ft_read_pipe.c \
		ft_utiles/ft_utile.c \
		ft_utiles/ft_utile2.c \
		ft_utiles/ft_get_value.c \
		ft_utiles/ft_print_error.c \
		ft_utiles/ft_split_mn.c \
		ft_builtins/ft_builtins.c \
		ft_builtins/signal.c \
		ft_builtins/utils.c \
		ft_builtins/export.c \
		ft_builtins/export_utils.c \
		ft_builtins/free.c \
		ft_builtins/environment.c \
		ft_builtins/environment_utils.c \
		ft_builtins/list.c \
		ft_builtins/env.c \
		ft_builtins/echo.c \
		ft_builtins/unset.c \
		ft_builtins/ft_cd.c \
		ft_builtins/ft_cd_utils.c \
		ft_builtins/exit.c \
		ft_builtins/pwd.c \
		ft_check_syntaxe/ft_check_syntaxe.c \
		ft_check_syntaxe/ft_check_syntaxe2.c \
		ft_check_syntaxe/ft_check_syntaxe3.c \
		ft_check_syntaxe/ft_check_syntaxe4.c \
		ft_check_syntaxe/ft_check_syntaxe5.c \
		ft_parsing/ft_parsing.c \
		ft_parsing/ft_parsing2.c \
		ft_parsing/ft_parsing3.c \
		ft_parsing/ft_parsing4.c \
		ft_parsing/ft_parsing5.c \
		ft_parsing/ft_parsing6.c \
		ft_parsing/ft_parsing7.c \
		ft_parsing/ft_parsing8.c \
		ft_parsing/ft_parsing9.c \
		ft_parsing/ft_parsing10.c \
		ft_parsing/ft_parsing_bonus.c \
		ft_run/ft_get_cmd.c \
		ft_run/ft_run.c \
		ft_run/ft_run_other_cmd.c \
		ft_run/ft_run_other_cmd2.c \
		ft_run/ft_run_with_pipe.c \
		ft_run/ft_run_bonus.c \
		ft_run/ft_cmd_special.c \
		ft_signe_dollar/ft_signe_dollar.c \
		ft_signe_dollar/ft_signe_dollar2.c \
		ft_signe_dollar/ft_signe_dollar3.c \
		ft_signe_dollar/del_unused_dollar.c \
		ft_signe_dollar/ft_signe_wave.c \
		ft_redirection/ft_redirection_input.c \
		ft_redirection/ft_redirection_output.c \
		ft_redirection/ft_redirection_output2.c \
		ft_redirection/ft_redirection_output3.c \
		ft_redirection/ft_find_limiter.c \
		ft_wildcards/ft_find_center.c \
		ft_wildcards/ft_find_end.c \
		ft_wildcards/ft_find_first.c \
		ft_wildcards/ft_wildcards2.c \
		ft_wildcards/ft_wildcards3.c \
		ft_wildcards/ft_wildcards.c \
		ft_wildcards/ft_wildcards_is_center.c

OBJ = $(SRC:.c=.o)

NAME = minishell

CC = gcc

READLINE = -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include

CFLAGS =  -Wall -Wextra -Werror

LIBFTPATH = ./libft

LIBFTS = $(LIBFTPATH)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(MAKE) -sC $(LIBFTPATH)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFTS) $(READLINE) -o $(NAME)
	@clear
	@echo "OK --> ./minishell"

$(OBJ): %.o: %.c Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) clean -sC ./libft
	@$(RM) $(OBJ)

fclean: clean
	@$(MAKE) fclean -sC ./libft
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
