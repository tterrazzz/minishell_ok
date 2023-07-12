/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:04:12 by avan              #+#    #+#             */
/*   Updated: 2022/11/22 15:51:05 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_length(char const *s1, char const *set, int *start)
{
	int	end;

	end = ft_strlen(s1);
	while (s1[*start] && ft_strchr(set, s1[*start]))
		*start = *start + 1;
	while (end > *start && ft_strchr(set, s1[end - 1]))
		end--;
	return (end - *start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_length(s1, set, &i);
	str = ft_substr(s1, i, j);
	if (str == NULL)
		return (NULL);
	return (str);
}
