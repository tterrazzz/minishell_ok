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
		while (current->redirection != NULL)
		{
			printf("filename :%s\ntype :%d\n", current->redirection->filename, current->redirection->type);
			current->redirection = current->redirection->next;
		}
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

static void	ft_fill_parsed(t_struct *s, t_parsed *current_parsed,
	t_token **current_token, int i)
{
	t_token		*prov;
	t_token		*useless;
	t_token		*begin;

	prov = *current_token;
	begin = NULL;
	while (prov != NULL && prov->type != pipex)
	{
		if (prov->type == 2 || prov->type == 3 || prov->type == 4
			|| prov->type == 5)
		{
			ft_node_add_back_redirec(current_parsed, prov->type);
			useless = prov->next;
			current_parsed->last_redire->filename = ft_strdup(useless->str);
			current_parsed->last_redire->filename
				= ft_dollar_check2(s, current_parsed->last_redire->filename);
			current_parsed->last_redire->filename
				= ft_quote_check2(current_parsed->last_redire->filename, 0, 0);
			ft_node_remove_token(s, prov);
			prov = useless;
			useless = prov->next;
			ft_node_remove_token(s, prov);
			prov = useless;
		}
		else
		{
			if (!begin)
				begin = prov;
			i++;
			prov = prov->next;
		}
	}
	current_parsed->command = malloc(sizeof(char *) * (i + 1));
	i = 0;
	*current_token = begin;
	if (*current_token != NULL)
	{
		while ((*current_token) != NULL && (*current_token)->type != pipex)
		{
			current_parsed->command[i] = ft_strdup((*current_token)->str);
			i++;
			*current_token = (*current_token)->next;
		}
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
