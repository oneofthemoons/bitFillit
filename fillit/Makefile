all:
	make -C ../libft/ fclean && make -C ../libft/
	gcc -Wextra -Wall -Werror main.c valid.c angle_moving.c to_binary.c permutations.c -L../libft -lft -o fillit -I ../libft
clear:
	rm -f *.o
	make -C ../libft/ clean
fclean: clear
	rm -f fillit
	rm -f ../libft/libft.a
re: fclean all
