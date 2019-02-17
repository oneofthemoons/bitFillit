/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:57:58 by hrickard          #+#    #+#             */
/*   Updated: 2019/02/17 13:07:19 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_binary_init(t_fig *arr_fig)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 26)
	{
		arr_fig[i].map_num = i;
		arr_fig[i].pos.x = 0;
		arr_fig[i].pos.y = 0;
		arr_fig[i].right = 0;
		arr_fig[i].down = 0;
		j = -1;
		while (++j < 4)
			arr_fig[i].st[j] = 0U;
	}
}

t_uint	ft_pow2(int pow)
{
	t_uint ans;

	ans = 1U;
	while (pow--)
		ans <<= 1;
	return (ans);
}

void	ft_to_binary(char *map, int count_fig, t_fig *arr_fig)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	ft_binary_init(arr_fig);
	while (++i < count_fig)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			while (++k < 4)
				if (map[i * 21 + j * 5 + k] == '#')
				{
					arr_fig[i].st[j] |= ft_pow2(k);
					if (j > arr_fig[i].down)
						arr_fig[i].down = j;
					if (k > arr_fig[i].right)
						arr_fig[i].right = k;
				}
		}
	}
}
