/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:57:58 by hrickard          #+#    #+#             */
/*   Updated: 2019/01/31 19:52:44 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void    ft_reset_placements(t_fig *arrFig, int n)
{
    int i;

    i = -1;
    while (++i < n)
    {
        arrFig[i].pos.x = 0;
        arrFig[i].pos.y = 0;
    }
}

int     ft_next_placement(t_fig *arrFig, int last_index, int range)
{
    if (arrFig[last_index].pos.x + arrFig[last_index].right >= range - 1 && arrFig[last_index].pos.y + arrFig[last_index].down >= range - 1 && last_index == 0)
    {
        arrFig[last_index].pos.x = 0;
        arrFig[last_index].pos.y = 0;
        return (0);
    }
    if (arrFig[last_index].pos.x + arrFig[last_index].right >= range - 1 && arrFig[last_index].pos.y + arrFig[last_index].down >= range - 1)
    {
        arrFig[last_index].pos.x = 0;
        arrFig[last_index].pos.y = 0;
        return (ft_next_placement(arrFig, last_index - 1, range));
    }
    if (arrFig[last_index].pos.x + arrFig[last_index].right >= range - 1)
    {
        arrFig[last_index].pos.x = 0;
        ++arrFig[last_index].pos.y;
        return (1);
    }
    ++arrFig[last_index].pos.x;
    return (1);
}