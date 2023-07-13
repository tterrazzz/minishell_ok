/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarbis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:03:30 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 19:44:32 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_advance_quoted(char *line, int *i)
{
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
	else if (line[*i] != '\"')
	{
		(*env_name)[*k] = line[*i];
		(*i)++;
		(*k)++;
	}
}
