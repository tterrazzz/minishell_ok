/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:16 by avan              #+#    #+#             */
/*   Updated: 2023/04/22 13:15:09 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	a;
	int		i;
	int		so;

	if (!s)
		return (NULL);
	i = 0;
	a = (char)c;
	so = -1;
	if (!a)
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == a)
			so = i;
		i++;
	}
	if (so == -1)
		return (NULL);
	return ((char *)&s[so]);
}
