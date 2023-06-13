/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutflag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:55:21 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:12:09 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_placeflag(t_elem *e, char c, int *i)
{
	if (!e)
		return ;
	if (c == '-')
		e->flags = e->flags | FLAG_MOINS;
	if (c == '0')
		e->flags = e->flags | FLAG_ZERO;
	if (c == '.')
		e->flags = e->flags | FLAG_POINT;
	if (c == '#')
		e->flags = e->flags | FLAG_HASHTAG;
	if (c == ' ')
		e->flags = e->flags | FLAG_ESPACE;
	if (c == '+')
		e->flags = e->flags | FLAG_PLUS;
	*i = *i + 1;
}

static void	ft_placetabint(const char *s, t_elem *e, int *nbr, int i)
{
	if ((s[0] == ' ' || s[0] == '+') && s[i] == '.' && e->flags & FLAG_ZERO)
		e->tabint[0] = *nbr;
	else if (s[0] == '.' && !(e->flags & FLAG_MOINS))
		e->tabint[1] = *nbr;
	else if (s[0] == '#' && s[i] != '.' && !(e->flags & FLAG_MOINS))
	{
		if (e->flags & FLAG_ZERO)
			e->tabint[1] = *nbr;
		else
			e->tabint[0] = *nbr;
	}
	else if (s[0] == '0' && s[i] != '.' && !(e->flags & FLAG_MOINS))
		e->tabint[1] = *nbr;
	else if ((s[0] == ' ' || s[0] == '+') && e->flags & FLAG_ZERO)
		e->tabint[1] = *nbr;
	else if (e->flags & FLAG_MOINS && e->flags & FLAG_POINT)
		e->tabint[1] = *nbr;
	else if (e->tabint[0] == 0)
		e->tabint[0] = *nbr;
	else
		e->tabint[1] = *nbr;
}

int	ft_cutflag(t_elem *e)
{
	int		i;
	int		nbr;
	char	*str;
	int		memo;

	i = 0;
	nbr = 0;
	memo = 0;
	str = e->elflag;
	while (str[i] && (ft_isflag(str[i]) || ft_isdigit(str[i])))
	{
		if (ft_isflag(str[i]))
			ft_placeflag(e, str[i], &i);
		if (str[i] >= '1' && str[i] <= '9')
		{
			if (i >= 1)
				memo = i - 1;
			while (str[i] && ft_isdigit(str[i]))
				nbr = nbr * 10 + (str[i++] - '0');
			ft_placetabint(&str[memo], e, &nbr, (i - memo));
			nbr = 0;
		}
	}
	return (i);
}
