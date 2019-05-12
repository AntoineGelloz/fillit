/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:34:44 by agelloz           #+#    #+#             */
/*   Updated: 2019/05/12 20:09:14 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_tetris	*add_fpiece2(char **tetris, int size)
{
	int			i;
	t_tetris	*new;

	i = -1;
	if (!(new = (t_tetris*)ft_memalloc(sizeof(t_tetris))))
		return (NULL);
	if (!(new->tetris = (char**)ft_memalloc(sizeof(char*) * size)))
		return (NULL);
	while (++i < (size - 1))
		if (!(new->tetris[i] = ft_strdup(tetris[i])))
			return (NULL);
	new->tetris[i] = NULL;
	new->next = NULL;
	return (new);
}

static t_tetris	*add_fpiece(t_tetris *pieces, char **tetris, int size)
{
	t_tetris *curr;

	if (!pieces)
		return (add_fpiece2(tetris, size));
	curr = pieces;
	while (curr && curr->next)
		curr = curr->next;
	if (!(curr->next = add_fpiece2(tetris, size)))
		return (NULL);
	return (pieces);
}

static void		get_dimensions(char **tetris, t_l *l)
{
	int			last_tok;
	int			f_seen;
	int			i;
	int			j;

	f_seen = 0;
	i = -1;
	last_tok = 0;
	while (tetris[++i])
	{
		j = -1;
		while (tetris[i][++j])
		{
			if (tetris[i][j] == '#' && (last_tok = j) >= 0)
			{
				if ((!f_seen || l->x > j) && (l->x = j) >= 0)
					if ((!f_seen && (f_seen = 1))
							&& (l->y = i) >= 0)
						l->maxx = 0;
				l->maxy = i;
			}
			else if (tetris[i][j] == '\n')
				l->maxx = (l->maxx < last_tok) ? last_tok : l->maxx;
		}
	}
}

char			**resize2(t_l l, t_tetris *curr)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!(tmp = (char**)malloc(sizeof(*tmp) * (l.maxy - l.y + 2))))
		return (NULL);
	i = l.y;
	tmp[l.maxy - l.y] = (char*)ft_memset(ft_strnew(1), '\n', 1);
	tmp[l.maxy - l.y + 1] = 0;
	while (i < l.maxy)
	{
		if (!(tmp[i - l.y] = (char*)malloc(l.maxx - l.x + 2)))
			return (NULL);
		ft_strncpy(tmp[i - l.y], curr->tetris[i] + l.x, l.maxx - l.x);
		tmp[i - l.y][l.maxx - l.x] = '\n';
		tmp[i - l.y][(l.maxx - l.x) + 1] = '\0';
		++i;
	}
	return (tmp);
}

t_tetris		*resize(t_tetris *old_pieces)
{
	t_tetris	*curr;
	t_tetris	*new_pieces;
	t_l			l;
	char		**tmp;

	curr = old_pieces;
	new_pieces = NULL;
	while (curr)
	{
		l.x = 0;
		l.y = 0;
		l.maxx = 0;
		l.maxy = 0;
		get_dimensions(curr->tetris, &l);
		++l.maxy;
		++l.maxx;
		tmp = resize2(l, curr);
		new_pieces = add_fpiece(new_pieces, tmp, l.maxy - l.y + 2);
		free_tmp(tmp, l.maxy - l.y + 2);
		curr = curr->next;
	}
	free_all_pieces(&old_pieces);
	return (new_pieces);
}
