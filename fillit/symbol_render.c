/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 13:02:50 by hrickard          #+#    #+#             */
/*   Updated: 2019/02/17 15:13:33 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_get_str_len(char *argv)
{
	int		str_len;
	int		fd;
	char	*buff;

	str_len = 0;
	if ((fd = open(argv, O_RDONLY)) == -1)
		ft_print_error(0);
	str_len = 0;
	while ((read(fd, &buff, 1) > 0) && str_len < 546)
		++str_len;
	close(fd);
	return (str_len);
}

int		ft_check_symbols(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '.' || map[i] == '#' || map[i] == '\n' || map[i] == '\0')
			i++;
		else
			return (0);
	}
	return (1);
}

int		ft_count_fig(char *map)
{
	int	hash;

	hash = 0;
	while (*map)
		if (*map++ == '#')
			++hash;
	return (hash >> 2);
}
