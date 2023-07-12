/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_givespeci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:57:32 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:12:44 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_givespeci(const char *arg)
{
	int		i;
	char	*str;

	if (!arg)
		return (-1);
	i = 0;
	str = (char *)arg;
	while (str[i])
	{
		if (ft_isspeci(str[i]))
			return (str[i]);
		i++;
	}
	return (0);
}
