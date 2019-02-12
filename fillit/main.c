#include "fillit.h"

#include <stdlib.h> //DEBUG

int     ft_count_fig(char *map)
{
    int hash;

    hash = 0;
    while (*map)
        if (*map++ == '#')
            ++hash;
    return (hash >> 2); // (hash / 4) fast equivalent
}

int     ft_minimal_range(t_fig *arrFig, int countFig)
{
    int rng;
    int i;

    rng = 1;
    while (rng * rng < (countFig << 2))
        ++rng;
    i = -1;
    while (++i < countFig)
    {
        if (rng <= arrFig[i].right)
            rng = arrFig[i].right + 1;
        if (rng <= arrFig[i].down)
            rng = arrFig[i].down + 1;
    }
    return (rng);
}

void    printBitMap(t_map bitMap)
{
    int i;
    int j;

    printf("bitmap:\n");
    i = -1;
    while (++i < bitMap.range)
    {
        j = -1;
        while (++j < bitMap.range)
            printf("%d", (bitMap.st[i] >> j) & 1);
        printf("\n");
    }
}

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


    bitMap.range = ft_minimal_range(arrFig, countFig) - 1;
    
    while (++bitMap.range < 26)
    {
        allIn = 0;
        ft_reset_placements(arrFig, countFig);

        while (ft_next_placement(arrFig, countFig - 1, bitMap.range))   // можно пропустить первый шаг, т.к. там все равно гарантировано пересечение фигур
        {
            ft_bzero(bitMap.st, 32 * sizeof(uint));
            allIn = 1;
            curFig = -1;
            while (++curFig < countFig)
            {
                figIn = 1;
                i = -1;
                while (++i < 4)
                    if ((arrFig[curFig].st[i] << arrFig[curFig].pos.x) & bitMap.st[arrFig[curFig].pos.y + i]) //if binary expr != 0
                    {
                        allIn = 0;
                        figIn = 0;
                        break;
                    }
                if (!figIn)
                    break;
                i = -1;
                while (++i < 4)
                    bitMap.st[arrFig[curFig].pos.y + i] |= (arrFig[curFig].st[i] << arrFig[curFig].pos.x);
                system("clear");
                printf("fig: %d\n", curFig);
                printBitMap(bitMap);
            }
            if (allIn)
                break;
        }
        if (allIn)
            break ;
    }
    printf("\n\n");




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
