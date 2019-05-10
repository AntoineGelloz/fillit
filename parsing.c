/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:20:41 by agelloz           #+#    #+#             */
/*   Updated: 2019/05/10 18:11:25 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "fillit.h"

void	initialize(char (*t)[131][5])
{
	int i;
	int j;

	i = 0;
	while (i < 131)
	{
		j = 0;
		while (j < 5)
		{
			(*t)[i][j] = '\0';
			j++;
		}
		i++;
	}
}

int		check_t(char t[131][5], int err)
{
	int i;
	int j;
	int ct;

	i = 0;
	ct = 0;
	while (i < 129)
	{
		j = -1;
		ct = (i % 5 == 4) ? 0 : ct;
		while (++j < 4)
		{
			ct = (t[i][j] == '#' && (t[i + 1][j] == '#')) ? ct + 1 : ct;
			ct = (t[i][j] == '#' && (i % 5 > 0 && t[i - 1][j] == '#'))
				? ct + 1 : ct;
			ct = (t[i][j] == '#' && (t[i][j + 1] == '#')) ? ct + 1 : ct;
			ct = (t[i][j] == '#' && j > 0 && t[i][j - 1] == '#') ? ct + 1 : ct;
			err = (!(t[0][0]) || (t[i][j] == '#' && ct == 0)) ? err + 1 : err;
			err = (t[i][j] == 'e' && i % 5 != 4) ? err + 1 : err;
		}
		i++;
		err = (i % 5 == 4 && t[i - 1][0] && ct != 6 && ct != 8) ? err + 1 : err;
	}
	return (err);
}

int		parse_line_2(char (**t)[131][5], char ***line, int *i, int *blocks)
{
	int		j;
	char	*p;
	int		err;

	err = 0;
	p = **line;
	while (*p)
	{
		err = (*p != '#' && *p != '.') ? err + 1 : err;
		*blocks = (*p == '#') ? *blocks + 1 : *blocks;
		p++;
	}
	p = **line;
	j = 0;
	while (*p && *i < 129 & j < 5)
		(**t)[*i][j++] = *p++;
	if (*i < 129)
		(**t)[*i + 1][0] = 'e';
	(*i)++;
	err = ((*i % 5 == 4 && *blocks != 4) || *i > 129) ? err + 1 : err;
	return (err);
}

int		parse_line(char (*t)[131][5], char **line)
{
	int			err;
	static int	blocks;
	static int	i;

	i = (!(*t)[0][0]) ? 0 : i;
	blocks = (i == 0) ? 0 : blocks;
	err = 0;
	if (!(**line))
	{
		err = (i == 0 || i % 5 != 4) ? err + 1 : err;
		blocks = (i % 5 == 4) ? 0 : blocks;
	}
	if (**line && ft_strlen(*line) != 4)
		err++;
	err += parse_line_2(&t, &line, &i, &blocks);
	ft_strdel(line);
	return (err);
}

int		main(int ac, char **av)
{
	int			err;
	int			fd;
	char		*line;
	char		t[131][5];

	fd = -1;
	line = NULL;
	err = 0;
	if (ac == 2)
	{
		initialize(&t);
		fd = open(av[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
			err += parse_line(&t, &line);
		err = check_t(t, err);
	}
	else
		ft_putendl("usage: ./fillit file");
	if (ac > 1 && (err || fd == -1))
		ft_putendl("error");
	(fd > -1) ? close(fd) : 1;
	//end of parsing > solving
	return (0);
}
