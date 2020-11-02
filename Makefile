all:
	gcc *.c ./get_next_line/*.c ./libft/ft_atoi.c -L. -lmlx -framework OpenGL -framework AppKit
	./a.out ./maps/map.cub
save:
	gcc *.c ./get_next_line/*.c ./libft/ft_atoi.c -L. -lmlx -framework OpenGL -framework AppKit
	./a.out ./maps/map.cub --save
