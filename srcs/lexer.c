#include "minishell.h"

// static int	ft_count_pipe(char *line)
// {
// 	int	i;
// 	int	count;

// 	if (!line)
// 		return (0);
// 	count = 0;
// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '|')
// 			count += 2;
// 		i++;
// 	}
// 	return (count);
// }

// /* add a apce before and after a pipe */
// char	*ft_add_space(char *line)
// {
// 	int		i;
// 	char	*str;
// 	int		count;
// 	int		y;

// 	i = 0;
// 	y = 0;
// 	count = ft_count_pipe(line);
// 	str = malloc(sizeof(char) * (count + ft_strlen(line) + 1));
// 	if (!str)
// 		return (NULL);
// 	while (line[i])
// 	{
// 		str[y] = line [i];
// 		if (line[i++] == '|')
// 		{
// 			str[y] = ' ';
// 			str[++y] = '|';
// 			str[++y] = ' ';
// 		}
// 		y++;
// 	}
// 	str[y] = '\0';
// 	free(line);
// 	return (str);
// }

// void	ft_lexer(t_struct *s, char *line)
// {
// 	char	**temp;
// 	int		i;

// 	i = -1;
// 	line = ft_add_space(line);
// 	temp = ft_minisplit(line, ' ');
// 	while (temp[++i])
// 		printf("temp de [%d] = [%s]\n", i, temp[i]);
// 	i = -1;
// 	printf("apres quote check\n");
// 	ft_struct_token(s, temp);
// 	if (!s->token)
// 		printf("s->token = NULL\n");
// 	while (s->token != NULL)
// 	{
// 		printf(" le token est : %s\n", s->token->str);
// 		printf("le token est de type : %d\n", s->token->type);
// 		s->token = s->token->next;
// 	}
// 	i = -1;
// 	while (temp[++i])
// 		free(temp[i]);
// 	free(temp);
// 	free(line);
// }

static void	ft_node_add_back_token(t_struct *s)
{
	t_token	*last;
	t_token	*temp;

	if (!s)
		return ;
	last = malloc(sizeof(t_token));
	if (!last)
		return ;
	last->next = NULL;
	last->c = '\0';
	last->type = cmd;
	if (!s->token)
		s->token = last;
	else
	{
		temp = s->token;
		while (temp->next)
			temp = temp->next;
		temp->next = last;
	}
}

static void	ft_tokenization(t_token *prov)
{
	if (prov->c == '>')
		prov->type = redirect_out;
	else if (prov->c == '<')
		prov->type = redirect_in;
	else if (prov->c == '|')
		prov->type = pipex;
	else if (prov->c == '\'')
		prov->type = quote;
	else if (prov->c == '\"')
		prov->type = double_quote;
	else if (prov->c == '-')
		prov->type = option;
	else if (prov->c == '$')
		prov->type = v_env;
	else if (prov->c == ' ')
		prov->type = space;
	else
		prov->type = cmd;
}

void	ft_lexer(t_struct *s, char *line)
{
	int		i;
	t_token	*prov;

	i = 0;
	while (line[i])
	{
		ft_node_add_back_token(s);
		if (i == 0)
			prov = s->token;
		else
			prov = prov->next;
		prov->c = line[i];
		ft_tokenization(prov);
		i++;
	}
	while (s->token != NULL)
	{
		printf(" le token est : %c\n", s->token->c);
		printf("le token est de type : %d\n", s->token->type);
		s->token = s->token->next;
	}
}
