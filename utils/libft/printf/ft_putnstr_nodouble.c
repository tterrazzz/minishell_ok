/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_nodouble.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:01:13 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:13:43 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnstr_nodouble(const char *s, int len, int *nbr)
{
	int		i;
	int		j;
	char	*str;
	char	*cpy;

	if (!s || !nbr)
		return ;
	i = 0;
	j = 0;
	str = (char *) s;
	cpy = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (cpy == NULL)
		return ;
	while (str[i] && i < len)
	{
		if (!ft_strchr(cpy, str[i]))
			cpy[j++] = str[i];
		i++;
	}
	cpy[j] = '\0';
	ft_putstr_printf(cpy, 1, nbr);
}
