#include "../srcs/minishell.h"

static void	ft_quote(char *str, int	*i, int *mot)
{
	if (str[*i] == '\"')
	{
		if ((*i) == 0 || str[(*i) - 1] == ' ')
			(*mot)++;
		(*i)++;
		if (str[*i] == '\"')
			return ;
		while (str[*i] && str[*i] != '\"')
			(*i)++;
	}
	if (str[*i] == '\'')
	{
		if ((*i) == 0 || str[(*i) - 1] == ' ')
			(*mot)++;
		(*i)++;
		if (str[*i] == '\'')
			return ;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	}
}

static int	ft_mot(char *str, char c, int i, int mot)
{
	int	x;

	while (str[i])
	{
		ft_quote(str, &i, &mot);
		x = i;
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && (str[i] != '\"' && str[i] != '\''))
			mot++;
		if (x != i)
		{
			ft_quote(str, &i, &mot);
			x = i;
		}
		while (str[i] && str[i] != c)
		{
			if ((str[i] == '\"' || str[i] == '\'') && (x != i))
			{
				ft_quote(str, &i, &mot);
			}
			i++;
		}
	}
	return (mot);
}

static void	ft_skip_quote(char *str, int *i)
{
	if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\"')
			(*i)++;
	}
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	}
}

char	**ft_minisplit(char *line, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (ft_mot(line, c, 0, 0) + 1));
	if (tab == NULL)
		return (NULL);
	while (line[i])
	{
		while (line[i] && line[i] == c)
			i++;
		start = i;
		while (line[i] && line[i] != c)
		{
			ft_skip_quote(line, &i);
			i++;
		}
		if (start != i)
			tab[j++] = ft_substr(line, start, i);
	}
	tab[j] = 0;
	return (tab);
}
