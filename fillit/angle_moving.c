/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_moving.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:57:58 by hrickard          #+#    #+#             */
/*   Updated: 2019/01/31 19:52:44 by hrickard         ###   ########.fr       */
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

void	ft_find_angle(char *map, const int len, t_pos *angle)
{
	int i;
	int j;
	int b;

	i = -1;
	while (++i < (len - len / 21) / 5)
	{
		if (ft_check_cell(map, i))
		{
			angle[i / 4].y = i + i / 4;
			b = -1;
			i = i - i % 4 + i / 4;
			while (++b < 4)
			{
				j = -1;
				while (++j < 4)
					if (map [i * 5 - 4 * (i / 5) + j * 5 + b] == '#')
						j = LOOP_EXIT_CODE;
				if (j - 1 == LOOP_EXIT_CODE)
					break;
			}
			angle[i / 5].x = b;
			i += 3 - i / 5;
		}
	}
}

void	ft_go_up_left(char* map, const int len)
{
	t_pos	*angle;
	int		i;
    int     j;
    int     k;
    char    t;

	i = -1;
	angle = (t_pos*)malloc(sizeof(t_pos) * (len + 1) / 21);
	ft_find_angle(map, len, angle);
    k = -1;
    while (++k < (len + 1) / 21)
    {
        i = -1;
        while (++i < 4 - angle[k].y % 5)
        {
            j = -1;
            while (++j < 4 - angle[k].x)
            {
                t = map[k * 21 + i * 5 + j];
                map[k * 21 + i * 5 + j] = map[(angle[k].y + i) * 5 - 4 * (angle[k].y / 5) + angle[k].x + j];
                map[(angle[k].y + i) * 5 - 4 * (angle[k].y / 5) + angle[k].x + j] = t;
            }
        }
    }
}