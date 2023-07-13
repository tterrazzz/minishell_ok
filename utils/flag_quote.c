/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:10:27 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:10:28 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	ft_flag_quote(t_struct *s, char c)
{
	if (c == '\'')
	{
		if (s->f_dquote == 0 && s->f_quote == 0)
			s->f_quote = 1;
		else if (s->f_dquote == 0 && s->f_quote == 1)
			s->f_quote = 0;
	}
	if (c == '\"')
	{
		if (s->f_dquote == 0 && s->f_quote == 0)
			s->f_dquote = 1;
		else if (s->f_dquote == 1 && s->f_quote == 0)
			s->f_dquote = 0;
	}
}

char	*ft_write_doubleredirec(char *str, int *i, int *y, int x)
{
	if (x == 1)
	{
		str[*y] = ' ';
		str[++(*y)] = '<';
		str[++(*y)] = '<';
		str[++(*y)] = ' ';
		(*i)++;
	}
	if (x == 2)
	{
		str[*y] = ' ';
		str[++(*y)] = '>';
		str[++(*y)] = '>';
		str[++(*y)] = ' ';
		(*i)++;
	}
	return (str);
}

char	*ft_write_redirec(char *str, int *y, int x)
{
	if (x == 1)
	{
		str[*y] = ' ';
		str[++(*y)] = '<';
		str[++(*y)] = ' ';
	}
	if (x == 2)
	{
		str[*y] = ' ';
		str[++(*y)] = '>';
		str[++(*y)] = ' ';
	}
	return (str);
}

char	*ft_write_space(char *str, int *y)
{
	str[*y] = ' ';
	str[++(*y)] = '|';
	str[++(*y)] = ' ';
	return (str);
}
