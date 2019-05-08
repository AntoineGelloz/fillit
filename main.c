/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:20:41 by agelloz           #+#    #+#             */
/*   Updated: 2019/05/08 21:17:42 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "fillit.h"

int				error(char **line, int fd, int code)
{
	ft_strdel(line);
	ft_putstr("error code ");
	ft_putnbr(code);
	ft_putchar('\n');
	close(fd);
	return (0);
}

void			initialize(char (*t)[104][4])
{
	int i;
	int j;

	i = 0;
	while (i < 104)
	{
		j = 0;
		while (j < 4)
		{
			(*t)[i][j] = '\0';
			j++;
		}
		i++;
	}
}

int				main(int ac, char **av)
{
	int			fd;
	char		*line;
	char		*p;
	int 		i;
	int 		j;
	int 		blocks;
	char		t[104][4];
	int			x;
	int			y;

	line = NULL;
	fd = -1;
	if (ac == 2)
	{
		initialize(&t);
		fd = open(av[1], O_RDONLY);
		i = 0;
		blocks = 0;
		while (get_next_line(fd, &line) > 0)
		{
			if (!*line)
			{
				if (i == 0 || i % 5 != 4)
					return (error(&line, fd, 1));
				else
					blocks = 0;
			}
			if (*line && ft_strlen(line) != 4)
				return (error(&line, fd, 2));
			p = line;
			while (*p)
			{
				if (*p != '#' && *p != '.')
					return (error(&line, fd, 3));
				else if (*p == '#')
					blocks++;
				p++;
			}
			if (i == 0 || i % 5 != 4)
			{
				p = line;
				j = 0;
				while (*p)
					t[i][j++] = *p++;
				ft_putendl(t[i]);
			}
			else
				ft_putchar('\n');
			if (i % 5 == 4 && blocks != 4)
				return (error(&line, fd, 4));
			i++;
			ft_strdel(&line);
		}
		if (i == 0 || i % 5 != 4)
			return (error(&line, fd, 5));
		close(fd);
		i = 0;
		while (i < 104)
		{
			j = 0;
			while (j < 4)
			{
				x = j % 4;
				y = i % 4;
				if (t[i][j] = '#')
				{
					if ((x == 2 || x == 3) && (y == 2 || y == 3)) //easy middle
						if (t[i + 1][j] != '#' && t[i - 1][j] != '#' && t[i][j + 1] != '#' && t[i][j - 1] != '#')
							return (error(&line, fd, 6));
					if (x == 1 && y == 1) //top left corner
						if (t[i][j + 1] != '#' && t[i + 1][j] != '#')
							return (error(&line, fd, 6));
					if (x == 4 && y == 1) //top right corner
						if (t[i][j - 1] != '#' && t[i + 1][j] != '#')
							return (error(&line, fd, 6));
					if (x == 1 && y == 4) //bottom left corner
						if (t[i][j + 1] != '#' && t[i - 1][j] != '#')
							return (error(&line, fd, 6));
					if (x == 4 && y == 4) //bottom right corner
						if (t[i][j - 1] != '#' && t[i][j - 1] != '#')
							return (error(&line, fd, 6));
				}
				j++;
			}
			i++;
		}
		ft_putendl("correct file");
	}
	else
		return (error(&line, fd, 6));
	return (0);
}
