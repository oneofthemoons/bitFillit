#include "fillit.h"

int     ft_count_fig(char *map)
{
    int hash;

    hash = 0;
    while (*map)
        if (*map++ == '#')
            ++hash;
    return (hash >> 2); // (hash / 4) fast equivalent
}

int    ft_minimal_range(int countFig)
{
    int rng;

    rng = 1;
    while (rng * rng < (countFig << 2))
        ++rng;
    return (rng);
}

void    ft_fig_pos_zero(t_fig *arrFig, int n)
{
    int i;

    i = -1;
    while (++i < n)
    {
        arrFig[i].pos.x = 0;
        arrFig[i].pos.y = 0;
    }
}

// void    printBitMap(t_map bitMap)
// {
//     int i;
//     int j;

//     printf("bitmap:\n");
//     i = -1;
//     while (++i < bitMap.range)
//     {
//         j = -1;
//         while (++j < bitMap.range)
//             printf("%d", (bitMap.st[i] >> j) & 1);
//         printf("\n");
//     }
// }

// void    printBitFig(t_fig fig)
// {
//     int i;
//     int j;

//     printf("fig:\n");
//     i = -1;
//     while (++i < 4)
//     {
//         j = -1;
//         while (++j < 4)
//             printf("%d", (fig.st[i] >> j) & 1);
//         printf("\n");
//     }
// }

int     main(int argc, char **argv)
{
    char    *map;
    t_fig   arrFig[26];
    t_map   bitMap;
    int     countFig;
    int     curFig;
    int     i;
    int     allIn;
    int     figIn;

    char    ans[26][27];
    int     j;

    map = get_map(argc, argv);
    countFig = ft_count_fig(map);
    ft_to_binary(map, countFig, arrFig);
    free(map);


    bitMap.range = ft_minimal_range(countFig) - 1;
    while (++bitMap.range < 26)
    {
        allIn = 0;
        ft_bzero(bitMap.st, 32 * sizeof(uint));
        ft_fig_pos_zero(arrFig, countFig);
        curFig = -1;
        while (++curFig < countFig)
        {
            allIn = 0;
            figIn = 0;
            while(!figIn)
            {
                if (bitMap.range <= arrFig[curFig].pos.x + arrFig[curFig].right ||
                    bitMap.range <= arrFig[curFig].pos.y + arrFig[curFig].down)
                    break ;
                figIn = 1;
                i = -1;
                while (++i < 4)
                {
                    if ((arrFig[curFig].st[i] << arrFig[curFig].pos.x) & bitMap.st[arrFig[curFig].pos.y + i]) //if binary expr != 0
                    {
                        figIn = 0;
                        ++arrFig[curFig].pos.x;
                        if (arrFig[curFig].pos.x + arrFig[curFig].right >= bitMap.range)
                        {
                            arrFig[curFig].pos.x = 0;
                            ++arrFig[curFig].pos.y;
                        }
                        break ;
                    }
                }
                i = -1;
                while (++i < 4 && figIn)
                    bitMap.st[arrFig[curFig].pos.y + i] |= (arrFig[curFig].st[i] << arrFig[curFig].pos.x);
                // printf("fig %d: pos.x = %d, pos.y = %d, figIn = %d\n", curFig, arrFig[curFig].pos.x, arrFig[curFig].pos.y, figIn);
                // printBitFig(arrFig[curFig]);
                // printBitMap(bitMap);
            }
            if (!figIn)
            {
                ft_bzero(bitMap.st, 32 * sizeof(uint));
                ft_fig_pos_zero(arrFig, countFig);
                curFig = -1;
                if (!ft_next_permutation(arrFig, countFig))
                {
                    ft_reset_permutations(arrFig, countFig);
                    break ;
                }
            }
            allIn = 1;
        }
        if (allIn)
            break ;
    }
    // printf("range: %d\n", bitMap.range);




    i = -1;
    while (++i < 26)
        ft_bzero(ans[i], 27 * sizeof(char));
    i = -1;
    while (++i < bitMap.range)
    {
        j = -1;
        while (++j < bitMap.range)
            ans[i][j] = '.';
    }
    curFig = -1;
    while (++curFig < countFig)
    {
        i = -1;
        while(++i < 4)
        {
            j = -1;
            while (++j < 4)
                if ((arrFig[curFig].st[i] >> j) & 1)
                    ans[arrFig[curFig].pos.y + i][arrFig[curFig].pos.x + j] = 'A' + arrFig[curFig].map_num;
        }
    }



    i = -1;
    while (++i < bitMap.range)
        printf("%s\n", ans[i]);
}
