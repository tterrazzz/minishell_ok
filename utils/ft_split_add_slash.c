/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_add_slash.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:51:46 by marvin            #+#    #+#             */
/*   Updated: 2023/06/01 16:51:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/pipex.h"

static void	ft_translation(char const *s, char c, int *i)
{
	int	j;

	j = 0;
	while (s[j] && s[j] == c)
		j++;
	*i = *i + j - 1;
}

static void	ft_translationdif(char const *s, char c, int *i, int nb)
{
	int	j;

	j = 0;
	(void) nb;
	while (s[j] && s[j] != c)
		j++;
	*i = *i + j - 1;
}

static char	*ft_deploiementmot(char const *strpos, char c, int *i)
{
	char	*str;
	char	*stock;
	int		j;

	j = 0;
	while (strpos[j] && strpos[j] != c)
		j++;
	stock = ft_substr(strpos, 0, j);
	str = ft_strjoin(stock, "/");
	free(stock);
	*i = *i + j - 1;
	return (str);
}

/*	ft_split_add_splash splits a string of characters using a character
	called c and adds one '/' at the end of each word
	it then returns a char **stock containing all the words */
char	**ft_split_add_slash(char const *s, char c)
{
	int			i;
	int			nb;
	char		**stock;

	if (!s)
		return (NULL);
	i = -1;
	nb = 0;
	while (s[++i])
	{
		if (s[i] == c)
			ft_translation(&s[i], c, &i);
		else if (s[i] != c)
			ft_translationdif(&s[i], c, &i, nb++);
	}
	stock = (char **) malloc(sizeof(char *) * (nb + 1));
	if (stock == NULL)
		return (NULL);
	i = -1;
	nb = 0;
	while (s[++i])
		if (s[i] != c)
			stock[nb++] = ft_deploiementmot(&s[i], c, &i);
	stock[nb] = NULL;
	return (stock);
}
