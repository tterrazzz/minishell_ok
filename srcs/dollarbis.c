/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarbis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurenc <llaurenc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:03:30 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 23:15:25 by llaurenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_advance_quoted(char *line, int *i)
{
	printf("line[%d] = %c\n", *i, line[*i]);
	(*i)++;
	while (line[*i] != '\'')
		(*i)++;
	(*i)++;
}

void	ft_fill_dollar(char *line, int *i, int *k, char **env_name)
{
	if (ft_isalpha(line[*i]) || line[*i] == '_')
	{
		while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		{
			(*env_name)[*k] = line[*i];
			(*i)++;
			(*k)++;
		}
	}
	else if (line[*i] != '\"' && line[*i] != '\'')
	{
		printf("la nononon\n\n");
		(*env_name)[*k] = line[*i];
		(*i)++;
		(*k)++;
	}
}
