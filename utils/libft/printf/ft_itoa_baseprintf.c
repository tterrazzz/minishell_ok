/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_baseprintf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:24:46 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:13:06 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_ifmorezeros(int count, t_elem *e, unsigned long long n)
{
	if (e->spe == 'p')
	{
		if (e->tabint[1] >= count)
			count = e->tabint[1];
		count += 2;
	}
	else
	{
		if (e->flags & FLAG_HASHTAG && n != 0)
		{
			count += 2;
			if (!(e->flags & FLAG_POINT) && e->tabint[1] > count)
				count = e->tabint[1];
			else if (e->flags & FLAG_POINT && e->tabint[1] > count - 2)
			{
				count = e->tabint[1];
				count += 2;
			}
		}
		else if (e->tabint[1] >= count)
			count = e->tabint[1];
	}
	return (count);
}

static int	ft_countchar(unsigned long long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	else
	{
		while (n > 0)
		{
			n = n / 16;
			count++;
		}
	}
	return (count);
}

static char	*ft_hashtagx(char *str, unsigned long long n, t_elem *e, int c)
{
	char	*base;

	if (e->spe == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	str[c] = '\0';
	if (n < 0)
		n *= -1;
	while (--c >= 2)
	{
		str[c] = base[n % 16];
		if (n > 0)
			n /= 16;
		else
			n = 0;
	}
	if (e->spe == 'X')
		str[1] = 'X';
	else
		str[1] = 'x';
	str[0] = '0';
	return (str);
}

static char	*ft_normalstrx(char *str, unsigned long long n, t_elem *e, int c)
{
	unsigned long long	size;
	char				*base;

	if (e->spe == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	size = ft_strlen(base);
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
	return (str);
}

void	ft_itoa_baseprintf(void *adr, t_elem *e)
{
	int					count;
	char				*str;
	int					i;
	unsigned long long	n;

	if (!e)
		return ;
	if (e->spe == 'p')
		n = (unsigned long long) adr;
	else
		n = (unsigned int) adr;
	i = 0;
	count = ft_ifmorezeros(ft_countchar(n), e, n);
	str = malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		return ;
	if (e->spe != 'p' && (!(e->flags & FLAG_HASHTAG) || n == 0))
		str = ft_normalstrx(str, n, e, count);
	else
		str = ft_hashtagx(str, n, e, count);
	e->s = str;
}
