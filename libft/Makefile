# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fflores <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/20 00:21:20 by fflores           #+#    #+#              #
#    Updated: 2020/06/01 11:19:21 by fflores          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = libft.h
FLAGS = -Wall -Wextra -Werror

SRC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
     	ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c \
	ft_strmapi.c ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c


SRC_OBJ = $(patsubst %.c,%.o,$(SRC))



all: $(NAME)

$(NAME): $(SRC_OBJ)
	ar rc $(NAME) $(SRC_OBJ)
	ranlib $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@
		
clean:
	/bin/rm -rf $(SRC_OBJ) $(BNS_OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all
