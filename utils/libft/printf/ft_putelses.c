/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putelses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:37:45 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:13:35 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putelses(t_elem *e, int *nb, int l, int temp)
{
	if (e->flags & FLAG_MOINS)
	{
		if (!e->tabint[1] && temp)
			ft_putchar_printf(' ', 1, nb);
		else if (temp || (!temp && e->tabint[1] == 1))
			ft_putchar_printf('0', 1, nb);
		while (e->tabint[0]-- > l)
			ft_putchar_printf(' ', 1, nb);
	}
	else
	{
		while (e->tabint[0]-- > l)
			ft_putchar_printf(' ', 1, nb);
		if (!e->tabint[1] && temp)
			ft_putchar_printf(' ', 1, nb);
		else if (temp || (!temp && e->tabint[1] == 1))
			ft_putchar_printf('0', 1, nb);
	}
}
