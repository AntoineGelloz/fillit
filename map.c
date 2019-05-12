/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemora <pemora@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 01:07:47 by pemora            #+#    #+#             */
/*   Updated: 2019/05/11 23:34:11 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	ft_rnd_sqrt(int nb)
{
	int sqrt;

	sqrt = 1;
	if (nb <= 0)
		return (0);
	while (sqrt <= 46340)
	{
		if (sqrt * sqrt >= nb)
			return (sqrt);
		sqrt++;
	}
	return (0);
}

char		**new_map_block(t_tetris *pieces, int size)
{
	int		i;
	char	**map;
	int		min;

	i = 0;
	while (pieces && ++i)
		pieces = pieces->next;
	min = ft_rnd_sqrt(i * 4);
	if (!(map = (char**)ft_memalloc(sizeof(char**) * (min + size + 1))))
		return (NULL);
	i = 0;
	while (i < min + size)
	{
		if (!(map[i] = ft_strnew(min + size)))
			return (NULL);
		i++;
	}
	map[i] = NULL;
	i = -1;
	while (++i < min + size)
		ft_memset(map[i], '.', min + size);
	return (map);
}

t_map		*new_map(t_tetris *pieces, int size)
{
	t_map	*board;

	if (!pieces)
		return (NULL);
	if (!(board = (t_map*)ft_memalloc(sizeof(t_map))))
		return (NULL);
	if (!(board->map = new_map_block(pieces, size)))
		return (NULL);
	board->size = ft_strlen(board->map[0]);
	return (board);
}
