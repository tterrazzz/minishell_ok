/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_giveindex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:01:03 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:12:35 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_giveindex(char speci)
{
	int		i;
	char	*comp;

	i = 0;
	comp = "diupxXcs%";
	while (comp[i])
	{
		if (comp[i] == speci)
			break ;
		i++;
	}
	if (i < 3)
		return (0);
	else if (i < 6)
		return (1);
	else
		return (2);
}
