/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:07:00 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:12:17 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_elem	*ft_enew(void)
{
	t_elem	*e;

	e = malloc(sizeof(t_elem));
	if (e == NULL)
		return (NULL);
	e->spe = 0;
	e->elflag = NULL;
	e->flags = 0;
	e->tabint[0] = 0;
	e->tabint[1] = 0;
	e->s = NULL;
	return (e);
}
