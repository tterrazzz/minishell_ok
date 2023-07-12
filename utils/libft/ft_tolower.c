/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:16:17 by avan              #+#    #+#             */
/*   Updated: 2022/11/09 17:04:37 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}

/*#include <ctype.h>
int	main(void)
{
	int	c;
	int	c2;

	c = 60;
	c2 = 60;
	printf("%d", ft_tolower(c));
	printf("%d", tolower(c2));
	return (0);
}*/
