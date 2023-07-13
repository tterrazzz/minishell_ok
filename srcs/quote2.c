/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:11:13 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:11:14 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_quote_replace(char *line, int start, int *i)
{
	char	*result;
	int		k;

	result = malloc(sizeof(char) * (ft_strlen(line) - 1));
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

char	*ft_quote_check2(char *line, int i, int start)
{
	while (line[i])
	{
		if (line[i] == '\"')
		{
			start = i;
			i++;
			while (line[i] != '\"')
				i++;
			line = ft_quote_replace(line, start, &i);
		}
		else if (line[i] == '\'')
		{
			start = i;
			i++;
			while (line[i] != '\'')
				i++;
			line = ft_quote_replace(line, start, &i);
		}
		i++;
	}
	return (line);
}
