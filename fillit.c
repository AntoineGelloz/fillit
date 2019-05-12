/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:34:39 by agelloz           #+#    #+#             */
/*   Updated: 2019/05/12 21:45:58 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "fillit.h"

static	int		test_empty_file(char *filename)
{
	char	*str;
	int		fd;

	if (!(str = ft_strnew(1)))
		return (-1);
	fd = open(filename, O_RDONLY);
	if (read(fd, str, 1) < 0 || *str == '\0' || (*str != '.' && *str != '#'))
	{
		free(str);
		str = NULL;
		return (-1);
	}
	free(str);
	str = NULL;
	close(fd);
	return (1);
}

int				main(int ac, char **av)
{
	int			fd;
	t_tetris	*pieces;

	if (ac != 2)
	{
		ft_putendl("usage: ./fillit file");
		return (0);
	}
	if (test_empty_file(av[1]) == -1)
	{
		ft_putendl("error");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	pieces = parse_file(fd);
	if (!(pieces))
		ft_putendl("error");
	else
		fill_it(pieces);
	return (0);
}
