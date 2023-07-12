/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:58:31 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:13:14 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_placingspaceplus(char **str, t_elem *e)
{
	if (e->flags & FLAG_PLUS)
	{
		*str[0] = '+';
		return ;
	}
	if (e->flags & FLAG_ESPACE)
		*str[0] = ' ';
}

static int	ft_ifmorezeros(long long n, int count, t_elem *e)
{
	if (e->tabint[1] > count || (e->tabint[1] >= count && n < 0))
	{
		count = e->tabint[1];
		if (e->flags & FLAG_ZERO && !e->tabint[0] && n >= 0)
		{
			if (e->flags & (FLAG_PLUS | FLAG_ESPACE))
			{
				if (!(e->flags & FLAG_POINT))
					count--;
			}
		}
		if (e->flags & FLAG_POINT && n < 0)
			count++;
	}
	if (e->flags & (FLAG_ESPACE | FLAG_PLUS) && n >= 0)
	{
		count++;
		if (e->flags & FLAG_POINT && e->tabint[1] < (count - 1))
			if (e->tabint[1] <= e->tabint[0] && n == 0)
				count--;
	}
	return (count);
}

static int	ft_countchar(long long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	else
	{
		if (n < 0)
		{
			n *= -1;
			count++;
		}
		while (n > 0)
		{
			n = n / 10;
			count++;
		}
	}
	return (count);
}

static char	*ft_fillstr(char *str, long long n, int c)
{
	long long	temp;
	long long	size;
	char		*base;

	base = "0123456789";
	size = ft_strlen(base);
	temp = n;
	str[c] = '\0';
	if (n < 0)
		n *= -1;
	while (--c >= 0)
	{
		str[c] = base[n % size];
		if (n > 0)
			n /= size;
		else
			n = 0;
	}
	if (temp < 0)
		str[0] = '-';
	return (str);
}

void	ft_itoa_i(void *adr, t_elem *e)
{
	int			count;
	char		*str;
	int			i;
	long long	n;

	i = 0;
	if (!e)
		return ;
	if (e->spe == 'i' || e->spe == 'd')
		n = (int) adr;
	else
		n = (unsigned int) adr;
	count = ft_ifmorezeros(n, ft_countchar(n), e);
	str = malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		return ;
	str = ft_fillstr(str, n, count);
	if (e->flags & (FLAG_ESPACE | FLAG_PLUS) && n >= 0)
		ft_placingspaceplus(&str, e);
	e->s = str;
}
