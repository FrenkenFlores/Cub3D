# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fflores <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 19:12:42 by fflores           #+#    #+#              #
#    Updated: 2020/11/02 19:12:44 by fflores          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ray_hit_wall.c config.c rays.c render_ceilling_floor.c \
	main.c screenshot.c get_floor_ceilling.c make_list.c sprite.c \
	sprite_list.c get_player_location.c get_resolution.c utils.c \
	get_tex_path.c mlx_utils.c walls.c key_input.c parser.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	check_double_key.c get_textures.c check_invalid_key.c


NAME = cub3D

OSRC = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

all: $(NAME) $(OSRC)

$(NAME): $(SRC)
	@make -C libft
	@make -C mlx_statlib
	@make -C mlx_dylib
	@cp libft/libft.a ./
	@cp mlx_statlib/libmlx.a ./
	@cp mlx_dylib/libmlx.dylib ./
	@gcc $(FLAGS) ./libft/libft.a ./mlx_statlib/libmlx.a ./mlx_dylib/libmlx.dylib -framework OpenGl -framework AppKit $(SRC) -o $(NAME)

clean:
	@make -C libft clean
	@rm -f $(OSRC)

fclean: clean
	@make -C libft fclean
	@make -C mlx_statlib clean
	@make -C mlx_dylib clean
	@rm -f libft.a
	@rm -f libmlx.a
	@rm -f libmlx.dylib
	@rm -f $(NAME)

re: fclean all

#all:
#	gcc *.c ./get_next_line/*.c ./libft/ft_atoi.c ./libft/ft_bzero.c ./libft/ft_strlen.c ./libft/ft_strncmp.c libmlx.a  -L mlx  -lmlx -framework OpenGL -framework AppKit -lz
#	./a.out ./maps/map.cub
#
#save:
#	gcc *.c ./get_next_line/*.c ./libft/ft_atoi.c libmlx.a  -L mlx  -lmlx -framework OpenGL -framework AppKit -lz
#	 ./a.out ./maps/map.cub --save
