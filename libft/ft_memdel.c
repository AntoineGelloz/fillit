/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:44:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/30 18:04:00 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Prend en parametre l'adresse d'un pointeur dont la zone pointee
** doit etre liberee avec free(3), puis le pointeur est mis a NULL.
*/

#include "libft.h"

void	ft_memdel(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
}
