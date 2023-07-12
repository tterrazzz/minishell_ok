/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:55:27 by marvin            #+#    #+#             */
/*   Updated: 2023/06/14 09:04:47 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_translation(char *str, char *tosearch)
{
	int	i;

	i = 0;
	while (tosearch[i])
	{
		if (str[i] != tosearch[i])
			return (0);
		i++;
	}
	return (1);
}

/*	ft_strnstr searches a needle string inside a haystack string within
	len size, it returns the adress of the first char if it finds needle
	in haystack, otherwise, it returns NULL */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*str;
	char	*tosearch;

	if (!haystack || !needle)
		return (NULL);
	str = (char *) haystack;
	tosearch = (char *) needle;
	if (*needle == 0)
		return (str);
	if (len == 0)
		return (NULL);
	len = len - ft_strlen(tosearch);
	i = 0;
	while (str[i] && i <= len)
	{
		if (ft_translation(&str[i], tosearch))
			return (&str[i]);
		i++;
	}
	return (NULL);
}
