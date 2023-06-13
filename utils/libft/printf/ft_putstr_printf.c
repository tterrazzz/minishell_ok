/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:35:59 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:13:54 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_printf(char *s, int fd, int *nbr)
{
	int	j;

	if (!s || !nbr)
		return ;
	else
	{
		j = 0;
		while (s[j])
			ft_putchar_printf(s[j++], fd, nbr);
	}
}
