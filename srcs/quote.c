#include "minishell.h"

static char	*ft_quote_replace(char *line, int start, int *i)
{
	char	*result;
	int		k;

	result = malloc(sizeof(char) * (ft_strlen(line) -1));
	k = 0;
	while (k != start)
	{
		result[k] = line[k];
		k++;
	}
	while (k != *i)
	{
		result[k] = line[k + 1];
		k++;
	}
	while (line[k])
	{
		result[k] = line[k + 2];
		k++;
	}
	result[k] = '\0';
	(*i) = (*i) - 2;
	free(line);
	return (result);
}

char	**ft_quote_check(t_struct *s, char **tab)
{
	int	i;
	int	j;
	int	start;

	(void)s;
	i = 0;
	j = -1;
	while (tab[++j])
	{
		i = 0;
		while (tab[j][i])
		{
			if (tab[j][i] == '\"')
			{
				start = i;
				i++;
				while (tab[j][i] != '\"')
					i++;
				tab[j] = ft_quote_replace(tab[j], start, &i);
			}
			i++;
		}
	}
	return (tab);
}
