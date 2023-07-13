#include "../srcs/minishell.h"

/*	static t_parsed *ft_create_parsed_node initialize a node of parsed */
static t_parsed	*ft_create_parsed_node(void)
{
	t_parsed	*parsed_node;
	int			i;

	parsed_node = malloc(sizeof(t_parsed));
	if (!parsed_node)
		return (NULL);
	i = 0;
	parsed_node->command = NULL;
	parsed_node->path = NULL;
	parsed_node->redirection = NULL;
	parsed_node->last_redire = NULL;
	parsed_node->here_d_pipe_fd = NULL;
	parsed_node->fd_in = 0;
	parsed_node->fd_out = 0;
	parsed_node->error = 0;
	parsed_node->next = NULL;
	parsed_node->prev = NULL;
	return (parsed_node);
}
/*	void ft_node_add_back_parsed creates a parsed node and adds it at
	the back of the parsed linked list */
void	ft_node_add_back_parsed(t_struct *s)
{
	t_parsed	*last;
	t_parsed	*temp;

	if (!s)
		return ;
	last = ft_create_parsed_node();
	if (!(s->parsed))
		s->parsed = last;
	else
	{
		temp = s->parsed;
		while (temp->next)
			temp = temp->next;
		last->prev = temp;
		temp->next = last;
	}
}

/*	void ft_node_add_back_envp_export creates a envp node and adds it at
	the back of the envp_export linked list */
/*void	ft_node_add_back_envp_export(t_struct *s, char **value, int i)
{
	t_envp	*last;
	t_envp	*temp;

	if (!s)
		return ;
	last = malloc(sizeof(t_envp));
	if (!last)
		return ;
	last->value = value;
	last->nb_words = i;
	last->next = NULL;
	last->prev = NULL;
	if (!s->envp_export)
		s->envp_export = last;
	else
	{
		temp = s->envp_export;
		while (temp->next)
			temp = temp->next;
		last->prev = temp;
		temp->next = last;
	}
}*/

/*	void ft_node_add_back_envp creates a envp node and adds it at
	the back of the envp linked list */
void	ft_node_add_back_envp(t_struct *s, char **value, int i)
{
	t_envp	*last;
	t_envp	*temp;

	if (!s || !value || (value && *value && !(**value)))
		return ;
	last = malloc(sizeof(t_envp));
	if (!last)
		return ;
	last->value = value;
	last->nb_words = i;
	last->next = NULL;
	last->prev = NULL;
	s->last_envp = last;
	if (!s->envp)
		s->envp = last;
	else
	{
		temp = s->envp;
		while (temp->next)
			temp = temp->next;
		last->prev = temp;
		temp->next = last;
	}
}

/*	void ft_node_add_back_token creates a token node and adds it at
	the back of the token linked list */
/*void	ft_node_add_back_token(t_struct *s, char *str)
{
	t_token	*last;
	t_token	*temp;

	if (!s || !str)
		return ;
	last = malloc(sizeof(t_token));
	if (!last)
		return ;
	last->str = str;
	last->next = NULL;
	last->prev = NULL;
	if (!(s->token))
		s->token = last;
	else
	{
		temp = s->token;
		while (temp->next)
			temp = temp->next;
		last->prev = temp;
		temp->next = last;
	}
}*/

void	ft_node_add_back_redirec(t_parsed **parsed, t_Tokentype type)
{
	t_redirec	*last;

	if (!parsed)
		return ;
	last = malloc(sizeof(t_redirec));
	if (!last)
		return ;
	last->next = NULL;
	last->prev = NULL;
	last->filename = NULL;
	last->here_d_pipe_fd = NULL;
	last->pid = 0;
	last->fd = 0;
	last->type = type;
	if (!((*parsed)->redirection))
		(*parsed)->redirection = last;
	if ((*parsed)->last_redire)
	{
		last->prev = (*parsed)->last_redire;
		(*parsed)->last_redire->next = last;
	}
	(*parsed)->last_redire = last;
}
