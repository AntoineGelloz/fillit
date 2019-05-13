/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:20:23 by agelloz           #+#    #+#             */
/*   Updated: 2019/05/13 13:06:30 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_tetris	*set_chars(t_tetris *pieces)
{
	t_tetris	*curr;
	int			i;
	int			n;
	char		chr;

	i = -1;
	n = -1;
	chr = 'A' - 1;
	curr = pieces;
	while (curr && ++chr)
	{
		while (curr->tetris[++i])
		{
			while (curr->tetris[i][++n])
				if (curr->tetris[i][n] == '#')
					curr->tetris[i][n] = chr;
			n = -1;
		}
		i = -1;
		curr = curr->next;
	}
	if (chr > 'Z')
		return (NULL);
	return (pieces);
}

static t_tetris	*get_piece_size(t_tetris *pieces)
{
	int			i;
	t_tetris	*curr;

	i = 0;
	curr = pieces;
	while (pieces)
	{
		pieces->width = ft_strlen(pieces->tetris[0]) - 1;
		while (pieces->tetris[i])
			i++;
		pieces->height = i - 1;
		i = 0;
		pieces = pieces->next;
	}
	return (curr);
}

static t_tetris	*add_piece2(char tetris[6][6])
{
	int			i;
	t_tetris	*new;

	i = -1;
	if (!(new = (t_tetris*)ft_memalloc(sizeof(t_tetris))))
		return (NULL);
	if (!(new->tetris = (char**)ft_memalloc(sizeof(char*) * 5)))
		return (NULL);
	while (++i < 4)
		if (!(new->tetris[i] = ft_strdup(tetris[i])))
			return (NULL);
	new->tetris[i] = NULL;
	new->next = NULL;
	return (new);
}

static t_tetris	*add_piece(t_tetris *pieces, char tetris[6][6])
{
	t_tetris *curr;

	curr = pieces;
	if (!(check_tetris(tetris)))
	{
		free_all_pieces(&pieces);
		return (NULL);
	}
	if (!pieces)
		return (add_piece2(tetris));
	while (curr && curr->next)
		curr = curr->next;
	if (!(curr->next = add_piece2(tetris)))
	{
		free_all_pieces(&pieces);
		return (NULL);
	}
	return (pieces);
}

t_tetris		*parse_file(int fd)
{
	int			i;
	char		tetris[6][6];
	char		*line;
	t_tetris	*pieces;
	int			err;

	i = 0;
	pieces = NULL;
	line = NULL;
	err = 0;
	initialize(&tetris);
	while (get_next_line(fd, &line) > 0)
	{
		err = ((i == 4 && *line) || ft_strlen(line) > 4) ? err + 1 : err;
		ft_strcpy(tetris[i], line);
		tetris[i][4] = '\n';
		err = (i == 3
			&& !(pieces = add_piece(pieces, tetris))) ? err + 1 : err;
		i == 4 ? (i = 0) : i++;
		ft_strdel(&line);
	}
	if (i < 3 || err)
		return (free_error(&pieces));
	pieces = set_chars(get_piece_size(resize(pieces)));
	return (pieces);
}
