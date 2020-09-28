# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fflores <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/03 10:43:46 by fflores           #+#    #+#              #
#    Updated: 2020/08/03 10:44:07 by fflores          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADER = ft_printf.h

FLAGS = -Wall -Werror -Wextra -c

SRC = ft_ch.c \
ft_check_parameters.c \
ft_check_str.c \
ft_combine_flags \
ft_get_precision.c \
ft_get_type.c \
ft_get_width.c \
ft_int_decimal.c \
ft_null_str.c \
ft_percent.c \
ft_pointer.c  \
ft_printf.c \
ft_str.c \
ft_unsigned.c \
ft_hex_full.c \
ft_hex_trunc.c \
ft_atoi.c\
ft_atoi_length.c\
ft_putchar.c\
ft_start.c\
ft_strlen.c\
ft_isdigit.c\
ft_strdup.c\
ft_set_flag.c\
ft_strjoin.c\
ft_flag_and_digit.c\
ft_type.c\
ft_hex_itoa.c


OBJ = ft_ch.o \
ft_check_parameters.o \
ft_check_str.o \
ft_combine_flags.o\
ft_get_precision.o \
ft_get_type.o \
ft_get_width.o \
ft_int_decimal.o \
ft_null_str.o \
ft_percent.o \
ft_pointer.o  \
ft_printf.o \
ft_str.o \
ft_unsigned.o \
ft_hex_full.o \
ft_hex_trunc.o \
ft_atoi.o\
ft_atoi_length.o\
ft_putchar.o\
ft_start.o\
ft_strlen.o\
ft_isdigit.o\
ft_strdup.o\
ft_set_flag.o\
ft_strjoin.o\
ft_flag_and_digit.o\
ft_type.o\
ft_hex_itoa.o

CC = gcc

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@ar rc $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -o $@ $<

clean:
	@ rm -f *.o

fclean: clean
	@ rm -f $(NAME)
	@ rm -f *.out

re: fclean all
