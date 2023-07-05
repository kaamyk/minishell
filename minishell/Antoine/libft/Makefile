# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 15:03:29 by anvincen          #+#    #+#              #
#    Updated: 2023/02/08 13:15:25 by anvincen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
SRCS	=	ft_isalnum.c	ft_isprint.c	ft_memcmp.c		ft_putchar_fd.c\
			ft_split.c		ft_strlcat.c	ft_strncmp.c	ft_substr.c\
			ft_atoi.c		ft_isalpha.c	ft_itoa.c		ft_memcpy.c\
			ft_putendl_fd.c	ft_strchr.c		ft_strlcpy.c	ft_strnstr.c\
			ft_tolower.c 	ft_bzero.c		ft_isascii.c	ft_memmove.c\
			ft_putnbr_fd.c	ft_strdup.c  	ft_strlen.c		ft_strrchr.c\
			ft_toupper.c	ft_calloc.c		ft_isdigit.c	ft_memchr.c\
			ft_memset.c		ft_putstr_fd.c	ft_strjoin.c	ft_strmapi.c\
			ft_strtrim.c	ft_striteri.c\
			ft_lstnew.c		ft_lstadd_front.c ft_lstadd_back.c ft_lstmap.c\
			ft_lstsize.c	ft_lstlast.c	ft_lstdelone.c 	ft_lstclear.c\
			ft_lstiter.c\
			ft_printf/srcs/ft_printf.c	ft_printf/srcs/ft_printf_utils.c\
			ft_printf/srcs/field.c		ft_printf/srcs/ft_printpar.c\
			ft_printf/srcs/ft_printpar_utils.c	ft_printf/srcs/print_c.c\
			ft_printf/srcs/print_d.c		ft_printf/srcs/print_o.c\
			ft_printf/srcs/print_p.c		ft_printf/srcs/print_pc.c\
			ft_printf/srcs/print_s.c		ft_printf/srcs/print_u.c\
			ft_printf/srcs/print_xX.c		ft_printf/srcs/set_0.c\
			ft_printf/srcs/set_plus.c		ft_printf/srcs/set_space.c\
			get_next_line/get_next_line.c	get_next_line/get_next_line_utils.c\

OBJS	=	$(SRCS:.c=.o)

FLAGS	=	-Werror -Wall -Wextra -g3

%.o:		%.c
		gcc $(FLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		ar rcs $(NAME) $(OBJS)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:			fclean	all
