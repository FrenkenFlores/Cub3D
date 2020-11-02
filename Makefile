all:
	gcc *.c ./get_next_line/*.c ./libft/ft_atoi.c libmlx.a  -L mlx  -lmlx -framework OpenGL -framework AppKit -lz
	./a.out ./maps/map.cub

save:
	gcc *.c ./get_next_line/*.c ./libft/ft_atoi.c libmlx.a  -L mlx  -lmlx -framework OpenGL -framework AppKit -lz
	 ./a.out ./maps/map.cub --save
