/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:57:14 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:12:30 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_findlen(const char *s, int *len)
{
	int		i;
	char	speci;
	char	*str;

	if (len < 0)
		return (-1);
	str = (char *) s;
	i = 1;
	speci = 0;
	while (str[i])
	{
		speci = ft_isspeci(str[i++]);
		if (speci)
		{
			return (1);
		}
		*len += 1;
	}
	return (-1);
}
