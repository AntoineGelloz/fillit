/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:42:14 by agelloz           #+#    #+#             */
/*   Updated: 2019/05/12 21:12:17 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetris	*free_error(t_tetris **pieces)
{
	free_all_pieces(pieces);
	return (NULL);
}

void		initialize(char (*tetris)[6][6])
{
	int	i;
	int	j;

	i = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 6)
		{
			(*tetris)[i][j] = '\0';
			j++;
		}
		i++;
	}
}

void		free_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
		ft_strdel(&map[i++]);
	free(map);
}

void		free_all_pieces(t_tetris **pieces)
{
	t_tetris	*free_piece;
	int			i;

	while (*pieces)
	{
		free_piece = *pieces;
		*pieces = (free_piece->next) ? free_piece->next : NULL;
		i = 0;
		while (free_piece->tetris[i])
			ft_strdel(&(free_piece->tetris[i++]));
		free(free_piece->tetris);
		free_piece->tetris = NULL;
		free(free_piece);
		free_piece = NULL;
	}
}

void		free_tmp(char **tmp, int height)
{
	int i;

	i = 0;
	while (i < height)
		ft_strdel(&tmp[i++]);
	free(tmp);
}
