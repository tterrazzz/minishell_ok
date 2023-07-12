/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalidflag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:58:07 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:13:01 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isvalidflag(const char *str, int i, int nbr)
{
	if (!str)
		return (0);
	if (str[i] >= '1' && str[i] <= '9')
	{
		while (str[i] && ft_isdigit(str[i]))
			i++;
		nbr++;
		if (str[i] != '.' && str[i])
			return (0);
	}
	while (str[i] && (ft_isflag(str[i]) || ft_isdigit(str[i])))
	{
		if (str[i] && ft_isflag(str[i]))
			i++;
		if (str[i] && str[i] >= '1' && str[i] <= '9' && nbr++ >= 0)
			while (str[i] && ft_isdigit(str[i]))
				i++;
	}
	if ((ft_strlen(str) != (size_t) i) || nbr > 2)
		return (0);
	if (i == 0)
		return (1);
	return (i);
}
