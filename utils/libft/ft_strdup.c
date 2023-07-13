/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:52:49 by marvin            #+#    #+#             */
/*   Updated: 2023/07/13 10:25:59 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	ft_strdup gets a string of char and returns a malloc copy of it */
/* char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*str;
	size_t	len;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
} */

char	*ft_strdup(char *s)
{
	char	*dup;
	int		i;

	if (!s)
		return (NULL);
	dup = malloc(sizeof(char) * (ft_strlen2(s) + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (s[++i])
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}
