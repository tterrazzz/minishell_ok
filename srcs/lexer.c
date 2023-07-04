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

/* add a apce before and after a pipe */
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
		if (line[i++] == '|')
		{
			str[y] = ' ';
			str[++y] = '|';
			str[++y] = ' ';
		}
		y++;
	}
	str[y] = '\0';
	free(line);
	return (str);
}

void	ft_lexer(t_struct *s, char *line)
{
	char	**temp;
	int		i;

	i = -1;
	line = ft_add_space(line);
	temp = ft_minisplit(line, ' ');
	while (temp[++i])
		printf("temp de [%d] = [%s]\n", i, temp[i]);
	temp = ft_dollar_check(s, temp);
	temp = ft_quote_check(s, temp);
	i = -1;
	printf("apres quote check\n");
	while (temp[++i])
		printf("temp de [%d] = [%s]\n", i, temp[i]);
	exit(0);
	ft_struct_token(s, temp);
	if (!s->token)
		printf("s->token = NULL\n");
	// while (s->token != NULL)
	// {
	// 	printf(" le token est : %s\n", s->token->str);
	// 	printf("le token est de type : %d\n",s->token->type);
	// 	s->token = s->token->next;
	// }
	i = -1;
	while (temp[++i])
		free(temp[i]);
	free(temp);
	free(line);
}
