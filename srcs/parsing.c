#include "minishell.h"

static void	print_parsed_list(t_parsed *parsed_list)
{
	t_parsed	*current;
	int			node_count;
	int			i;

	current = parsed_list;
	node_count = 0;
	while (current != NULL)
	{
		printf("Node %d:\n", node_count);
		if (current->command != NULL)
		{
			i = 0;
			while (current->command[i] != NULL)
			{
				printf("%s\n", current->command[i]);
				i++;
			}
		}
		else
		{
			printf("No commands in this node.\n");
		}
		printf("\n");
		current = current->next;
		node_count++;
	}
}

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
	// (*parsed_node)->pipe_fd = NULL;
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

// static void	ft_fill_temp(t_struct *s, t_token **current_token, int i)
// {
// 	char		**temp;
// 	t_token		*prov;

// 	printf("Fill temp\n");
// 	prov = *current_token;
// 	while (prov != NULL && prov->type != pipex)
// 	{
// 		if (prov->type == redirection)
// 			ft_choper prochain token
// 		else
// 			i++;
// 		prov = prov->next;
// 	}
// 	temp = malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	while ((*current_token) != NULL && (*current_token)->type != pipex)
// 	{
// 		temp[i] = ft_strdup((*current_token)->str);
// 		i++;
// 		*current_token = (*current_token)->next;
// 	}
// 	temp[i] = NULL;
// 	ft_node_add_back_parsed(s, temp);
// 	i = 0;
// 	while (temp[i])
// 		free(temp[i++]);
// 	free(temp);
// }

// void	ft_parsing(t_struct *s)
// {
// 	t_token		*current_token;
// 	t_parsed	*current_parsed;
// 	int			i;

// 	printf("parsing\n");
// 	i = 0;
// 	current_token = s->token;
// 	current_parsed = s->parsed;
// 	while (current_token != NULL)
// 	{
// 		printf("current token = %s\n", current_token->str);
// 		ft_fill_temp(s, &current_token, 0);
// 		if (current_token != NULL)
// 			current_token = current_token->next;
// 	}
// 	// while (s->parsed->command[i])
// 	// 	free(s->parsed->command[i++]);
// 	// free(s->parsed->command);
// 	// free(s->parsed);
// 	// free(s->token->str);
// 	// free(s->token);
// 	//system("leaks minishell");
// 	ft_node_add_back_parsed(s, NULL);
// 	current_parsed = s->parsed;
// 	while (current_token)
// 	{
// 		if (current_token->type == '|')
// 		{
// 			ft_node_add_back_parsed(s, NULL);
// 			current_token->type = current_token->next;
// 			current_parsed = current_parsed->next;
// 		}
// 		ft_fill_parsed(current_parsed, &current_token);
// 		current_token = current_token->next;
// 	}

// 	print_parsed_list(s->parsed);
// }

static void	ft_fill_parsed(t_struct *s, t_parsed *current_parsed,
	t_token **current_token, int i)
{
	t_token		*prov;
	t_token		*useless;

	(void)s;
	prov = *current_token;
	printf("FILL\n");
	while (prov != NULL && prov->type != pipex)
	{
		if (prov->type == 2 || prov->type == 3 || prov->type == 4
			|| prov->type == 5)
		{
			ft_node_add_back_redirec(current_parsed, prov->type);
			useless = prov->next;
			ft_node_remove_token(s, prov);
			prov = useless;
			current_parsed->redirection->filename = prov->str;
			useless = prov->next;
			ft_node_remove_token(s, prov);
			prov = useless;
		}
		else
		{
			i++;
			prov = prov->next;
		}
	}
	current_parsed->command = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((*current_token) != NULL && (*current_token)->type != pipex)
	{
		current_parsed->command[i] = ft_strdup((*current_token)->str);
		printf("command de [%d] = %s\n", i, current_parsed->command[i]);
		i++;
		*current_token = (*current_token)->next;
	}
	current_parsed->command[i] = NULL;
}

void	ft_parsing(t_struct *s)
{
	t_token		*current_token;
	t_parsed	*current_parsed;

	current_token = s->token;
	ft_node_add_back_parsed(s);
	current_parsed = s->parsed;
	while (current_token != NULL)
	{
		if (current_token->type == 1)
		{
			printf("PIPEX\n");
			ft_node_add_back_parsed(s);
			current_token = current_token->next;
			current_parsed = current_parsed->next;
		}
		ft_fill_parsed(s, current_parsed, &current_token, 0);
		current_parsed->command 
			= ft_dollar_check(s, current_parsed->command, -1);
		current_parsed->command
			= ft_quote_check(current_parsed->command, -1, 0, 0);
	}
	print_parsed_list(s->parsed);
}

// static void	ft_fill_parsed(t_parsed *current_parsed, t_token **current_token)
// {
// 	if (!current_parsed || !current_token)
// 		return ;
// 	if ((*current_token)->type == 2 || (*current_token)->type == 3
// 		|| (*current_token)->type == 4 || (*current_token)->type == 5)
// 	{
// 		ft_node_add_back_redirec(current_parsed, (*current_token)->type);
// 	}
// 	else
// 	{

// 	}
// }

