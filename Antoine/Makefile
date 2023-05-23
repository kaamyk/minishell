# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 15:03:29 by anvincen          #+#    #+#              #
#    Updated: 2023/05/23 17:29:31 by anvincen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#antoine/Makefile
NAME			=	minishell

MINISHELLSRCS	=	main.c\

MINISHELLOBJS	=	$(MINISHELLSRCS:.c=.o)

LIBFTPATH		=	./libft

LIBFT			=	$(LIBFTPATH)/libft.a

INCLUDES		=	-I ./libft/ -lreadline

CC				=	cc

FLAGS			=	-Wall -Wextra -Werror -g3

all:			$(NAME)

$(NAME):		$(LIBFT) $(MINISHELLOBJS)
			$(CC) $(FLAGS) $(INCLUDES) $(MINISHELLOBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
			make -sC $(LIBFTPATH)

clean:
			rm -f $(MINISHELLOBJS)
			make -sC $(LIBFTPATH) clean 

fclean:			clean
			rm -f $(NAME)
			rm -f $(LIBFT)

re:				fclean	all
