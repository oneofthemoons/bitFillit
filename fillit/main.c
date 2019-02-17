/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:46:32 by hrickard          #+#    #+#             */
/*   Updated: 2019/02/17 14:46:35 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_minimal_range(t_fig *arr, int n_fig)
{
	int	rng;
	int	i;

	rng = 1;
	while (rng * rng < (n_fig << 2))
		++rng;
	i = -1;
	while (++i < n_fig)
	{
		if (rng <= arr[i].right)
			rng = arr[i].right + 1;
		if (rng <= arr[i].down)
			rng = arr[i].down + 1;
	}
	return (rng);
}

void	ft_check_putin(t_fig *arr, t_map *bit, int n_fig, int *all)
{
	int	cur;
	int	in;
	int	i;

	cur = -1;
	while (++cur < n_fig)
	{
		in = 1;
		i = -1;
		while (++i < 4)
			if (arr[cur].st[i] << arr[cur].pos.x &
					bit->st[arr[cur].pos.y + i] ||
					arr[cur].pos.x + arr[cur].right >= bit->range ||
					arr[cur].pos.y + arr[cur].down >= bit->range)
			{
				*all = 0;
				in = 0;
				break ;
			}
		if (!in)
			break ;
		i = -1;
		while (++i < 4)
			bit->st[arr[cur].pos.y + i] |= (arr[cur].st[i] << arr[cur].pos.x);
	}
}

void	ft_prepare_map(t_map *bit, char ans[26][27])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 26)
		ft_bzero(ans[i], 27 * sizeof(char));
	i = -1;
	while (++i < bit->range)
	{
		j = -1;
		while (++j < bit->range)
			ans[i][j] = '.';
	}
}

void	ft_edro(t_fig *arr, t_map *bit, int n_fig)
{
	char	ans[26][27];
	int		cur;
	int		i;
	int		j;

	ft_prepare_map(bit, ans);
	cur = -1;
	while (++cur < n_fig)
	{
		i = -1;
		while (++i < 4)
		{
			j = -1;
			while (++j < 4)
				if ((arr[cur].st[i] >> j) & 1)
					ans[arr[cur].pos.y + i][arr[cur].pos.x + j] =
					'A' + arr[cur].map_num;
		}
	}
	i = -1;
	while (++i < bit->range)
		ft_putendl(ans[i]);
}

int		main(int argc, char **argv)
{
	char	*map;
	t_fig	arr[26];
	t_map	bit;
	int		n_fig;
	int		all;

	all = 0;
	map = ft_get_map(argc, argv);
	n_fig = ft_count_fig(map);
	ft_to_binary(map, n_fig, arr);
	free(map);
	bit.range = ft_minimal_range(arr, n_fig) - 1;
	while (!all && ++bit.range < 26)
	{
		ft_reset_placements(arr, n_fig);
		while (!all && ft_next_placement(arr, n_fig - 1, bit.range))
		{
			all = 1;
			ft_bzero(bit.st, 32 * sizeof(int));
			ft_check_putin(arr, &bit, n_fig, &all);
		}
	}
	ft_edro(arr, &bit, n_fig);
}
