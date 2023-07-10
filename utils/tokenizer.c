#include "../srcs/minishell.h"

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
	last->str = NULL;
	last->prev = NULL;
	last->type = cmd;
	if (!s->token)
		s->token = last;
	else
	{
		temp = s->token;
		while (temp->next)
			temp = temp->next;
		last->prev = temp;
		temp->next = last;
	}
}

static void	ft_tokenization(t_token *prov)
{
	if (prov->str[0] == '\0')
		prov->type = cmd;
	else if (prov->str[1] && prov->str[0] == '<' && prov->str[1] == '<')
		prov->type = double_redirect_in;
	else if (prov->str[1] && prov->str[0] == '>' && prov->str[1] == '>')
		prov->type = double_redirect_out;
	else if (prov->str[0] == '>')
		prov->type = redirect_out;
	else if (prov->str[0] == '<')
		prov->type = redirect_in;
	else if (prov->str[0] == '|')
		prov->type = pipex;
	else if (prov->str[0] == '\'')
		prov->type = quote;
	else if (prov->str[0] == '\"')
		prov->type = double_quote;
	else if (prov->str[0] == '-')
		prov->type = option;
	else if (prov->str[0] == '$')
		prov->type = v_env;
	else
		prov->type = cmd;
}

void	ft_struct_token(t_struct *s, char **temp)
{
	t_token	*prov;
	int		i;

	if (!s)
		return ;
	i = 0;
	while (temp[i])
	{
		ft_node_add_back_token(s);
		if (i == 0)
			prov = s->token;
		else
			prov = prov->next;
		prov->str = ft_strdup(temp[i]);
		ft_tokenization(prov);
		i++;
	}
	return ;
}