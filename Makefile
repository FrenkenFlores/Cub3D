all:
	gcc main.c ./get_next_line/*.c ./libft/ft_atoi.c -lmlx -framework OpenGL -framework AppKit -lz
	./a.out ./maps/map.cub
