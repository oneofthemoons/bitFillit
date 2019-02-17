/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_moving.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 15:11:58 by hrickard          #+#    #+#             */
/*   Updated: 2019/02/17 15:12:01 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_check_cell(char *map, int i)
{
	int j;
	int b;

	b = 0;
	j = -1;
	while (++j < 5)
		if (map[i * 5 + i / 4 + j] == '#')
			b = 1;
	return (b);
}

void	ft_find_angle(char *map, const int len, t_pos *an)
{
	int i;
	int j;
	int b;

	i = -1;
	while (++i < (len - len / 21) / 5)
	{
		if (ft_check_cell(map, i))
		{
			an[i / 4].y = i + i / 4;
			b = -1;
			i = i - i % 4 + i / 4;
			while (++b < 4)
			{
				j = -1;
				while (++j < 4)
					if (map[i * 5 - 4 * (i / 5) + j * 5 + b] == '#')
						j = LOOP_EXIT_CODE;
				if (j - 1 == LOOP_EXIT_CODE)
					break ;
			}
			an[i / 5].x = b;
			i += 3 - i / 5;
		}
	}
}

void	ft_go_up_left(char *map, const int len)
{
	t_pos	*an;
	int		i;
	int		j;
	int		k;
	char	t;

	i = -1;
	an = (t_pos*)malloc(sizeof(t_pos) * (len + 1) / 21);
	ft_find_angle(map, len, an);
	k = -1;
	while (++k < (len + 1) / 21)
	{
		i = -1;
		while (++i < 4 - an[k].y % 5)
		{
			j = -1;
			while (++j < 4 - an[k].x)
			{
				t = map[k * 21 + i * 5 + j];
				map[k * 21 + i * 5 + j] = map[(an[k].y + i) * 5 - 4 *
					(an[k].y / 5) + an[k].x + j];
				map[(an[k].y + i) * 5 - 4 * (an[k].y / 5) + an[k].x + j] = t;
			}
		}
	}
}
