/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:14:59 by avan              #+#    #+#             */
/*   Updated: 2022/11/14 11:50:20 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*ptrdst;
	const char	*ptrsrc;
	size_t		i;

	if (!dst && !src)
		return (0);
	ptrdst = dst;
	ptrsrc = src;
	i = 0;
	if (dst > src)
	{
		while (len)
		{
			ptrdst[len - 1] = ptrsrc[len - 1];
			len--;
		}
		return (dst);
	}
	while (i < len)
	{
		ptrdst[i] = ptrsrc[i];
		i++;
	}
	return (dst);
}
