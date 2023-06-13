/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_printf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:00:04 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:13:50 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnstr_printf(const char *s, int len, int *nbr)
{
	int		i;
	char	*str;

	if (!s || nbr < 0)
		return ;
	i = 0;
	str = (char *) s;
	while (str[i] && i < len)
	{
		ft_putchar_printf(str[i], 1, nbr);
		i++;
	}
}
