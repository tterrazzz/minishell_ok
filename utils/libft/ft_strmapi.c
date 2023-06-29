/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurenc <llaurenc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:24:58 by avan              #+#    #+#             */
/*   Updated: 2023/06/27 15:11:05 by llaurenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (!s || !f)
		return (ft_strdup(""));
	i = 0;
	str = ft_strdup((char *)s);
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str);
}
