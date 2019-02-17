/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:57:58 by hrickard          #+#    #+#             */
/*   Updated: 2019/02/17 13:31:23 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_reset_placements(t_fig *arr, int n)
{
	int i;

	i = -1;
	while (++i < n)
	{
		arr[i].pos.x = 0;
		arr[i].pos.y = 0;
	}
}

void	ft_fig_move(t_fig *arr, int last, int rng)
{
	if (arr[last].pos.x + arr[last].right >= rng - 1)
	{
		arr[last].pos.x = 0;
		++arr[last].pos.y;
	}
	else
		++arr[last].pos.x;
}

void	ft_try_putin(t_fig *arr, t_map *map, int end, int fig_in)
{
	int cur;
	int i;

	cur = -1;
	while (++cur < end)
	{
		i = -1;
		while (++i < 4)
			map->st[arr[cur].pos.y + i] |= (arr[cur].st[i] << arr[cur].pos.x);
	}
	while (!fig_in)
	{
		fig_in = 1;
		i = -1;
		while (++i < 4)
			if (arr[end].st[i] << arr[end].pos.x & map->st[arr[end].pos.y + i])
				fig_in = 0;
		if (fig_in)
			break ;
		if (arr[end].pos.x + arr[end].right >= map->range - 1 &&
				arr[end].pos.y + arr[end].down >= map->range - 1)
			break ;
		ft_fig_move(arr, end, map->range);
	}
}

int		ft_next_placement(t_fig *arr, int last, int rng)
{
	t_map	map;
	int		fig_in;

	if (arr[last].pos.x + arr[last].right >= rng - 1 &&
			arr[last].pos.y + arr[last].down >= rng - 1 && last == 0)
	{
		arr[last].pos.x = 0;
		arr[last].pos.y = 0;
		return (0);
	}
	if (arr[last].pos.x + arr[last].right >= rng - 1 &&
			arr[last].pos.y + arr[last].down >= rng - 1)
	{
		arr[last].pos.x = 0;
		arr[last].pos.y = 0;
		return (ft_next_placement(arr, last - 1, rng));
	}
	ft_fig_move(arr, last, rng);
	fig_in = 0;
	ft_bzero(map.st, 32 * sizeof(int));
	map.range = rng;
	ft_try_putin(arr, &map, last, fig_in);
	return (1);
}
