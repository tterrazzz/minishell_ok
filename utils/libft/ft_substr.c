/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:56:01 by marvin            #+#    #+#             */
/*   Updated: 2023/07/12 18:48:48 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	ft_substr creates and returns a malloc string of a portion or complete
	part of a s string from the start position to the len size */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(((len - start + 1) * sizeof(char)));
	if (!ret)
		return (NULL);
	while (start < len)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_substr_quote(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(((1 + (len - start)) * sizeof(char)));
	if (!ret)
		return (NULL);
	while (start < len)
	{
		if (s[start] == '\"')
		{
			ret[i++] = '\"';
			start++;
		}
		else if (s[start] == '\'')
		{
			ret[i++] = '\'';
			start++;
		}
		else
			ret[i++] = s[start++];
	}
	ret[i] = '\0';
	return (ret);
}