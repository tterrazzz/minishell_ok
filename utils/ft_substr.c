/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:56:01 by marvin            #+#    #+#             */
/*   Updated: 2023/06/05 14:08:10 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/pipex.h"

/*	ft_substr creates and returns a malloc string of a portion or complete
	part of a s string from the start position to the len size */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start >= l)
		return (ft_strdup(""));
	l = l - start + 1;
	if (l > len)
		l = len + 1;
	str = malloc(sizeof(char) * l);
	if (!str)
		return (str);
	l = ft_strlcpy(str, &s[start], l);
	return (str);
}
