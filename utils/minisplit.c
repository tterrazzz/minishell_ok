#include "../srcs/minishell.h"

static void	ft_quote(char *str, int	*i, int *mot)
{
	if (str[*i] == '\"')
	{
		if ((*i) == 0 || str[(*i) - 1] == ' ')
			(*mot)++;
		(*i)++;
		while (str[*i] && str[*i] != '\"')
			(*i)++;
		(*i)++;
	}
	if (str[*i] == '\'')
	{
		if ((*i) == 0 || str[(*i) - 1] == ' ')
			(*mot)++;
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		(*i)++;
	}
}

static int	ft_mot(char *str, char c)
{
	int	i;
	int	mot;

	i = 0;
	mot = 0;
	while (str[i])
	{
		ft_quote(str, &i, &mot);
		while (str[i] && str[i] == c)
			i++;
		ft_quote(str, &i, &mot);
		if (str[i])
			mot++;
		while (str[i] && str[i] != c)
		{
			ft_quote(str, &i, &mot);
			i++;
		}
	}
	printf("i : %d et mot : %d\n", i, mot);
	return (mot);
}

// static void	ft_split_quote(char **tab, char *str, int *i, int *j)
// {
// 	int	start;

// 	if (str[*i] == '\"')
// 	{
// 		(*i)++;
// 		start = (*i);
// 		while (str[*i] && str[*i] != '\"')
// 			(*i)++;
// 		if (start != (*i))
// 			tab[(*j)++] = ft_substr(str, start, *i);
// 		(*i)++;
// 	}
// 	if (str[*i] == '\'')
// 	{
// 		(*i)++;
// 		start = (*i);
// 		while (str[*i] && str[*i] != '\'')
// 			(*i)++;
// 		if (start != (*i))
// 			tab[(*j)++] = ft_substr(str, start, *i);
// 		(*i)++;
// 	}
// }

char	**ft_minisplit(char *line, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (ft_mot(line, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (line[i])
	{
		//ft_split_quote(tab, line, &i, &j);
		while (line[i] && line[i] == c)
			i++;
		//ft_split_quote(tab, line, &i, &j);
		start = i;
		while (line[i] && line[i] != c)
		{
			//ft_split_quote(tab, line, &i, &j);
			i++;
		}
		if (start != i)
		{
			tab[j] = ft_substr(line, start, i);
			printf("start = [%d] = %c\ni = [%d] = %c\n", start, line[start], i, line[i]);
			printf(" tab [%d] = %s\n", j, tab[j]);
			j++;
		}
		tab[j] = NULL;
	}
	return (tab);
}

// int	main(int argc, char **argv)
// {
// 	int	i;
// 	int	mot;

// 	(void)argc;
// 	i = 0;
// 	mot = 0;
// 	printf("%c\n", argv[1][7]);
// 	printf("%c\n", argv[1][8]);
// 	printf("%c\n", argv[1][9]);
// 	printf("%c\n", argv[1][10]);
// 	ft_mot(argv[1], ' ');
// 	printf("%c\n", argv[1][8]);
// }