/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:57:58 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/01/31 19:52:44 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_print_error(int signal)
{
	if (signal == 0)
		write(1, "error\n", 6);
	else if (signal == -1)
		write(1, "usage:./fillit your_file\n", 25);
	exit(EXIT_SUCCESS);
}

int		ft_check_map(char *map)
{
	int	i;
	int	row;

	row = 1;
	i = -1;
	while (map[++i])
	{
		if ((map[i + 4] == '\n') && (row % 5 != 0))
		{
			row++;
			i += 4;
		}
		else if (map[i] == '\n' && (!(row % 5)))
			row++;
		else
			break ;
	}
	if (row % 5 != 0)
		return (0);
	if (map[i] == '\0')
		return (row - 1);
	return (0);
}

int		is_figure_valid(char *map)
{
	int	i;
	int	hash;
	int	figure;

	i = -1;
	hash = 0;
	figure = 0;
	while (map[++i])
	{
		if (map[i] == '#')
		{
			(i + 1 < 21 && map[i + 1] == '#') ? figure++ : figure;
			(i + 5 < 21 && map[i + 5] == '#') ? figure++ : figure;
			(i - 1 >= 0 && map[i - 1] == '#') ? figure++ : figure;
			(i - 1 >= 0 && map[i - 5] == '#') ? figure++ : figure;
			hash++;
		}
	}
	if ((figure == 6 || figure == 8) && hash == 4)
		return (1);
	return (0);
}

int		ft_check_square(char *map, int len)
{
	int		i;
	char	square[21];

	ft_bzero(square, 21);
	i = -1;
	while (map[++i])
	{
		ft_strncpy(square, &map[i], 20);
		if (!(is_figure_valid(square)))
			return (0);
		i += 20;
		if (i >= len)
			break ;
	}
	return (1);
}

char	*ft_get_map(int argc, char **argv)
{
	int		fd;
	int		str_len;
	int		i;
	char	buff;
	char	*map;

	if (argc != 2)
		ft_print_error(-1);
	fd = -1;
	str_len = ft_get_str_len(argv[1]);
	if ((str_len < 20 || str_len > 545) || !(fd = open(argv[1], O_RDONLY)))
		ft_print_error(0);
	map = (char*)malloc(sizeof(char) * (str_len + 1));
	i = 0;
	while ((read(fd, &buff, 1) > 0))
		map[i++] = buff;
	map[i] = '\0';
	close(fd);
	if (!(ft_check_map(*(&map))) || (!(ft_check_symbols(*(&map)))))
		ft_print_error(0);
	if (!(ft_check_square(map, str_len)))
		ft_print_error(0);
	ft_go_up_left(map, str_len);
	return (map);
}
