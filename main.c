/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:20:41 by agelloz           #+#    #+#             */
/*   Updated: 2019/05/09 18:47:16 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "fillit.h"

void	initialize(char (*t)[130][5])
{
	int i;
	int j;

	i = 0;
	while (i < 130)
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

void	fill_tetriminos(char (*t)[130][5], char **line, int i)
{
	
}

int		check_contacts(char t[130][5], int errors)
{
	int i;
	int j;
	int contacts;

	i = 0;
	contacts = 0;
	while (i < 129)
	{
		j = -1;
		contacts = (i % 5 == 4) ? 0 : contacts;
		while (++j < 4)
		{
			if (t[i][j] == '#')
			{
				contacts = (t[i + 1][j] == '#') ? contacts + 1 : contacts;
				contacts = (i % 5 > 0 && t[i - 1][j] == '#') ? contacts + 1 : contacts;
				contacts = (t[i][j + 1] == '#') ? contacts + 1 : contacts;
				contacts = (j > 0 && t[i][j - 1] == '#') ? contacts + 1 : contacts;
				errors = (contacts == 0) ? errors + 1 : errors;
			}
		}
		i++;
		errors = (i % 5 == 4 && t[i - 1][0] && contacts != 6 && contacts != 8) ? errors + 1 : errors;
	}
	return (errors);
}

int		main(int ac, char **av)
{
	int			errors;
	int			fd;
	char		*line;
	char		*p;
	int 		i;
	int 		j;
	int 		blocks;
	char		t[130][5];

	fd = -1;
	line = NULL;
	errors = 0;
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
					errors++;
				else
					blocks = 0;
			}
			if (*line && ft_strlen(line) != 4)
				errors++;
			p = line;
			while (*p)
			{
				if (*p != '#' && *p != '.')
				{
					errors++;
					close(fd);
				}
				else if (*p == '#')
					blocks++;
				p++;
			}
			if ((i == 0 || i % 5 != 4) && i < 129)
			{
				p = line;
				j = 0;
				while (*p)
					t[i][j++] = *p++;
			}
			i++;
			if (i % 5 == 4 && blocks != 4)
				errors++;
			ft_strdel(&line);
		}
		if (i == 0 || i % 5 != 4 || i > 129)
			errors++;
		close(fd);
		errors = check_contacts(t, errors);
	}
	else
		ft_putendl("usage: ./fillit file");
	if (errors)
	{
		ft_putendl("error");
		(fd != -1) ? close(fd) : 1;
	}
	return (0);
}
