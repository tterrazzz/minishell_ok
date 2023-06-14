#include "minishell.h"

static int	ft_count_pipe(char *line)
{
	int	i;
	int	count;

	if (!line)
		return (0);
	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			count += 2;
		i++;
	}
	return (count);
}

char	*ft_add_space(char *line)
{
	int		i;
	char	*str;
	int		count;
	int		y;

	i = 0;
	y = 0;
	count = ft_count_pipe(line);
	str = malloc(sizeof(char) * (count + ft_strlen(line) + 1));
	if (!str)
		return (NULL);
	while (line[i])
	{
		str[y] = line [i];
		if (line[i] == '|')
		{
			str[y] = ' ';
			str[++y] = '|';
			str[++y] = ' ';
		}
		i++;
		y++;
	}
	free(line);
	return (str);
}

void	ft_lexer(t_struct *s, char *line)
{
	char	**temp;

	(void) s;
	line = ft_add_space(line);
	temp = ft_split(line, ' ');
	printf("%s")
}