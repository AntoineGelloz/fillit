/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 12:02:11 by agelloz           #+#    #+#             */
/*   Updated: 2019/05/12 20:50:27 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fillit.h"

static int	valid_format(char tetris[6][6])
{
	int	i;
	int	j;
	int	n;

	n = 0;
	i = -1;
	j = -1;
	while (tetris[++i][0])
	{
		while (tetris[i][++j])
		{
			if ((tetris[i][j] != '#' && tetris[i][j] != '.'
				&& tetris[i][j] != '\n') || (j == 4 && tetris[i][j] != '\n'))
				return (0);
			if (tetris[i][j] == '#')
				n++;
		}
		if (i > 4 || (j != 5 && j != 1))
			return (0);
		j = -1;
	}
	return (n != 4 ? 0 : 1);
}

static int	count_links(char tetris[6][6], int x, int y)
{
	int count;

	count = 0;
	if (x < 3 && tetris[y][x + 1] == '#')
		count++;
	if (x > 0 && tetris[y][x - 1] == '#')
		count++;
	if (y < 3 && tetris[y + 1][x] == '#')
		count++;
	if (y > 0 && tetris[y - 1][x] == '#')
		count++;
	return (count);
}

int			check_tetris(char tetris[6][6])
{
	int x;
	int y;
	int count;

	if (!(valid_format(tetris)))
		return (0);
	count = 0;
	x = 0;
	y = 0;
	while (tetris[y][0])
	{
		while (tetris[y][x])
		{
			if (tetris[y][x] == '#')
				count += count_links(tetris, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	if (count != 8 && count != 6)
		return (0);
	return (1);
}
