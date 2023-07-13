/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:11:23 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:11:24 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_quote_replace(char *line, int start, int *i)
{
	char	*result;
	int		k;

	result = malloc(sizeof(char) * (ft_strlen(line) -1));
	k = 0;
	while (k != start)
	{
		result[k] = line[k];
		k++;
	}
	while (k + 1 != *i)
	{
		result[k] = line[k + 1];
		k++;
	}
	while (line[k + 2])
	{
		result[k] = line[k + 2];
		k++;
	}
	*i = *i - 2;
	result[k] = '\0';
	free(line);
	return (result);
}

char	**ft_quote_check(char **tab, int j, int i, int start)
{
	while (tab[++j])
	{
		i = 0;
		while (tab[j][i])
		{
			if (tab[j][i] == '\"')
			{
				start = i;
				i++;
				while (tab[j][i] != '\"')
					i++;
				tab[j] = ft_quote_replace(tab[j], start, &i);
			}
			else if (tab[j][i] == '\'')
			{
				start = i;
				i++;
				while (tab[j][i] != '\'')
					i++;
				tab[j] = ft_quote_replace(tab[j], start, &i);
			}
			i++;
		}
	}
	return (tab);
}
