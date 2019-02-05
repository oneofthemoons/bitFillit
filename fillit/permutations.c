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

void    ft_swap_fig(t_fig *arrFig, int i, int j)
{
    t_fig temp = arrFig[i];
    arrFig[i] = arrFig[j];
    arrFig[j] = temp;
}

void    ft_reset_permutations(t_fig *arrFig, int n)
{
    int i;

    i = -1;
    while (++i < n / 2)
        ft_swap_fig(arrFig, i, n - 1 - i);
}

int     ft_next_permutation(t_fig *arrFig, int n)
{
    int j;
    int k;

    if (n < 2)
        return (0);
    j = n - 2;
    while (j != -1 && arrFig[j].map_num >= arrFig[j + 1].map_num)
        --j;
    if (j == -1)
        return (0);
    k = n - 1;
    while (arrFig[j].map_num >= arrFig[k].map_num)
        --k;
    ft_swap_fig(arrFig, j, k);
    j = j + 1;
    k = n - 1;
    while (j < k)
        ft_swap_fig(arrFig, j++, k--);
    return (1);
}