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
    t_map   bitMap;
    int     figIn;
    int     curFig;
    int     i;

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
        }
    else
        ++arrFig[last_index].pos.x;

    figIn = 0;
    curFig = -1;
    ft_bzero(bitMap.st, 32 * sizeof(int));
    bitMap.range = range;
    while (++curFig < last_index)
    {
        i = -1;
        while (++i < 4)
            bitMap.st[arrFig[curFig].pos.y + i] |= (arrFig[curFig].st[i] << arrFig[curFig].pos.x);
    }
    while (!figIn)
    {
        figIn = 1;

        i = -1;
        while (++i < 4)
            if ((arrFig[last_index].st[i] << arrFig[last_index].pos.x) & bitMap.st[arrFig[last_index].pos.y + i]) //if binary expr != 0
                figIn = 0;
        if (figIn)
            break;
        
        if (arrFig[last_index].pos.x + arrFig[last_index].right >= range - 1 && arrFig[last_index].pos.y + arrFig[last_index].down >= range - 1)
        {
            break;
        }
        if (arrFig[last_index].pos.x + arrFig[last_index].right >= range - 1)
        {
            arrFig[last_index].pos.x = 0;
            ++arrFig[last_index].pos.y;
        }
        else
            ++arrFig[last_index].pos.x;
        // printf("index: %d, pos.x: %d, pos.y: %d, figIn: %d\n", last_index, arrFig[last_index].pos.x, arrFig[last_index].pos.y, figIn);
        // printBitMap(bitMap);
        // if (arrFig[last_index].pos.x + arrFig[last_index].right >= range - 1 && arrFig[last_index].pos.y + arrFig[last_index].down >= range - 1)
        // {
        //     break;
        // }
    }
    return (1);
}