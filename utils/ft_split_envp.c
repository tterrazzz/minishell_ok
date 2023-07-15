/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:09:59 by avan              #+#    #+#             */
/*   Updated: 2023/07/15 08:29:26 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

static int	ft_count_words(char const *s, int *i)
{
	int	nb;

	if (!s)
		return (0);
	nb = 1;
	while (s[*i])
	{
		if (s[*i] == '=')
		{
			nb++;
			break ;
		}
		*i += 1;
	}
	return (nb);
}

char	**ft_split_envp(char const *s, int *nb)
{
	int			i;
	char		**stock;

	if (!s || !nb)
		return (NULL);
	i = 0;
	*nb = ft_count_words(s, &i);
	stock = (char **) malloc(sizeof(char *) * 3);
	if (stock == NULL)
		return (NULL);
	stock[0] = ft_substr(s, 0, i);
	if (*nb == 2)
		stock[1] = ft_substr(s, i + 1, ft_strlen(s));
	stock[*nb] = NULL;
	if (*nb == 1)
	{
		stock[1] = NULL;
		stock[2] = NULL;
	}
	return (stock);
}
