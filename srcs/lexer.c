/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:38:47 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 19:40:58 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lexer(t_struct *s, char *line)
{
	char	**temp;
	int		i;

	s->f_dquote = 0;
	s->f_quote = 0;
	line = ft_add_space(s, line);
	temp = ft_minisplit(line, ' ');
	ft_struct_token(s, temp);
	i = -1;
	while (temp[++i])
		free(temp[i]);
	free(temp);
	free(line);
}
