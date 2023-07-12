/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:52:49 by marvin            #+#    #+#             */
/*   Updated: 2023/06/14 09:03:36 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	ft_strdup gets a string of char and returns a malloc copy of it */
char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;
	int		len;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
