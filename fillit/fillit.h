#ifndef FILLIT_H
# define FILLIT_H
# define MAX_SIZE 104
# define LOOP_EXIT_CODE 8072000

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "libft.h"

//CLEAR ^

typedef unsigned int uint;

typedef struct  s_pos
{
    int         x;
    int         y;
}               t_pos;

typedef struct  s_fig
{
    uint        st[4];
    t_pos       pos;
    int         right;
    int         down;
    uint        map_num;
}               t_fig;

typedef struct  s_map
{
    uint        st[32];
    int        range;
}               t_map;


char    *get_map(int argc, char **argv);
void	ft_go_up_left(char* map, const int len);
void    ft_to_binary(char *map, int countFig, t_fig *arrFig);
int     ft_next_permutation(t_fig *arrFig, int n);
void    ft_reset_permutations(t_fig *arrFig, int n);

#endif