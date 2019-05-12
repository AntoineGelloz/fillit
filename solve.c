/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:50:46 by agelloz           #+#    #+#             */
/*   Updated: 2019/05/12 19:40:49 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	fits(t_tetris *pieces, char **map, int col, int row)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pieces->tetris[i])
	{
		while (pieces->tetris[i][j] && pieces->tetris[i][j] != '\n')
		{
			if (pieces->tetris[i][j] != '.' && map[row + i][col + j] != '.')
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

static int	place_piece(t_tetris *pieces, char **map, int col, int row)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (!(fits(pieces, map, col, row)))
		return (0);
	while (pieces->tetris[++i])
	{
		while (pieces->tetris[i][++j] && pieces->tetris[i][j] != '\n')
		{
			if (pieces->tetris[i][j] != '.')
				map[row + i][col + j] = pieces->tetris[i][j];
		}
		j = -1;
	}
	return (1);
}

static void	remove_piece(char **tetris, char **map)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	while (tetris[0][++i])
		if (tetris[0][i] != '.')
			break ;
	c = tetris[0][i];
	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j])
			if (map[i][j] == c)
				map[i][j] = '.';
		j = -1;
	}
}

static int	solve(t_tetris *pieces, t_map *board, int col, int row)
{
	if (!pieces)
		return (1);
	while (board->map[row] && ((board->size - row) >= pieces->height))
	{
		while (board->map[row][col] && ((board->size - col) >= pieces->width))
		{
			if (place_piece(pieces, board->map, col, row))
			{
				if (solve(pieces->next, board, 0, 0))
					return (1);
				remove_piece(pieces->tetris, board->map);
			}
			col++;
		}
		row++;
		col = 0;
	}
	return (0);
}

int			fill_it(t_tetris *pieces)
{
	t_map	*board;
	int		size;
	int		i;

	size = 0;
	if (!(board = new_map(pieces, 0)))
		return (-1);
	while (!solve(pieces, board, 0, 0))
	{
		size++;
		free_map(board->map);
		free(board);
		if (!(board = new_map(pieces, size)))
			return (-1);
	}
	i = -1;
	while (board->map[++i])
		ft_putendl(board->map[i]);
	free_all_pieces(&pieces);
	free_map(board->map);
	free(board);
	return (1);
}
