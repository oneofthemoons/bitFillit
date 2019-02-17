/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:51:18 by hrickard          #+#    #+#             */
/*   Updated: 2019/02/17 15:01:21 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define MAX_SIZE 104
# define LOOP_EXIT_CODE 8072000

# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"

typedef unsigned int	t_uint;

typedef struct			s_pos
{
	int					x;
	int					y;
}						t_pos;

typedef struct			s_fig
{
	t_uint				st[4];
	t_pos				pos;
	int					right;
	int					down;
	t_uint				map_num;
}						t_fig;

typedef struct			s_map
{
	t_uint				st[32];
	int					range;
}						t_map;

char					*ft_get_map(int argc, char **argv);
void					ft_go_up_left(char *map, const int len);
void					ft_to_binary(char *map, int n_fig, t_fig *arr);
int						ft_next_placement(t_fig *arr, int last_index,
						int range);
void					ft_reset_placements(t_fig *arr, int n);
int						ft_get_str_len(char *argv);
int						ft_check_symbols(char *map);
void					ft_print_error(int signal);
int						ft_count_fig(char *map);
#endif
