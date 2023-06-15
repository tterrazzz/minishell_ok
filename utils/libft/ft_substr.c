/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurenc <llaurenc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:56:01 by marvin            #+#    #+#             */
/*   Updated: 2023/06/15 13:33:48 by llaurenc         ###   ########.fr       */
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

