/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:44:18 by agelloz           #+#    #+#             */
/*   Updated: 2019/05/13 17:55:01 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "libft.h"

# define BUFF_SIZE 20

typedef struct			s_tetris
{
	char				**tetris;
	int					height;
	int					width;
	struct s_tetris		*next;
}						t_tetris;

typedef struct			s_map
{
	char				**map;
	int					size;
}						t_map;

typedef struct			s_l
{
	int					x;
	int					y;
	int					maxx;
	int					maxy;
}						t_l;

void					initialize(char (*tetris)[6][6]);
int						get_next_line(const int fd, char **line);
t_tetris				*parse_file(int fd);
t_tetris				*resize(t_tetris *old_pieces);
int						fill_it(t_tetris *pieces);
int						check_tetris(char tetris[6][6]);
t_map					*new_map(t_tetris *pieces, int size);
void					free_all_pieces(t_tetris **pieces);
void					free_tmp(char **tmp, int height);
void					free_map(char **map);
t_tetris				*free_error(t_tetris **pieces);
#endif
