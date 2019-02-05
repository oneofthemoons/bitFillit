/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:57:58 by hrickard          #+#    #+#             */
/*   Updated: 2019/01/31 19:52:44 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void    ft_binary_init(t_fig *arrFig)
{
    int i;
    int j;

    i = -1;
    while (++i < 26)
    {
        arrFig[i].map_num = i;
        arrFig[i].pos.x = 0;
        arrFig[i].pos.y = 0;
        arrFig[i].right = 0;
        arrFig[i].down = 0;
        j = -1;
        while (++j < 4)
            arrFig[i].st[j] = 0U;
    }
}

uint    ft_pow2(int pow)
{
    uint ans;

    ans = 1U;
    while (pow--)
        ans <<= 1; //fast *=2 equivalent
    return(ans);
}

void    ft_to_binary(char *map, int countFig, t_fig *arrFig)
{
    int i;
    int j;
    int k;

    i = -1;
    ft_binary_init(arrFig);
    while (++i < countFig)
    {
        j = -1;
        while (++j < 4)
        {
            k = -1;
            while (++k < 4)
                if (map[i * 21 + j * 5 + k] == '#')
                {
                    arrFig[i].st[j] |= ft_pow2(k);
                    if (j > arrFig[i].down)
                        arrFig[i].down = j;
                    if (k > arrFig[i].right)
                        arrFig[i].right = k;
                }
        }
        // printf("%d: right = %d, down = %d\n", i, arrFig[i].right, arrFig[i].down);
    }
}