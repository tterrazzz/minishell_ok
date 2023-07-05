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

static void	ft_fill_parsed_node(t_parsed **parsed_node, char **cmd_copy)
{
	(*parsed_node)->command = cmd_copy;
	(*parsed_node)->path = NULL;
	(*parsed_node)->redirection = NULL;
	(*parsed_node)->last_redire = NULL;
	// (*parsed_node)->pipe_fd = NULL;
	(*parsed_node)->here_d_pipe_fd = NULL;
	(*parsed_node)->fd_in = 0;
	(*parsed_node)->fd_out = 0;
	(*parsed_node)->error = 0;
	(*parsed_node)->next = NULL;
	(*parsed_node)->prev = NULL;
}

static t_parsed	*ft_create_parsed_node(char **command)
{
	t_parsed	*parsed_node;
	char		**command_copy;
	int			i;

	parsed_node = malloc(sizeof(t_parsed));
	if (!parsed_node)
		return (NULL);
		i = 0;
	while (command[i] != NULL)
		i++;
	command_copy = malloc((i + 1) * sizeof(char *));
	if (!command_copy)
	{
		free(parsed_node);
		return (NULL);
	}
	i = 0;
	while (command[i] != NULL)
	{
		command_copy[i] = ft_strdup(command[i]);
		i++;
	}
	command_copy[i] = NULL;
	ft_fill_parsed_node(&parsed_node, command_copy);
	return (parsed_node);
}

/*	void ft_node_add_back_parsed creates a parsed node and adds it at
	the back of the parsed linked list */
void	ft_node_add_back_parsed(t_struct *s, char **command)
{
	t_parsed	*last;
	t_parsed	*temp;

	if (!s)
		return ;
	last = ft_create_parsed_node(command);
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

static void	ft_fill_temp(t_struct *s, t_token **current_token, int i)
{
	char		**temp;
	t_token		*prov;

	printf("Fill temp\n");
	prov = *current_token;
	while (prov != NULL && prov->type != pipex)
	{
		i++;
		prov = prov->next;
	}
	temp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((*current_token) != NULL && (*current_token)->type != pipex)
	{
		temp[i] = ft_strdup((*current_token)->str);
		i++;
		*current_token = (*current_token)->next;
	}
	temp[i] = NULL;
	ft_node_add_back_parsed(s, temp);
	i = 0;
	while (temp[i])
		free(temp[i++]);
	free(temp);
}


void	ft_parsing(t_struct *s)
{
	t_token		*current_token;
	t_parsed	*current_parsed;
	int			i;

	printf("parsing\n");
	i = 0;
	current_token = s->token;
	current_parsed = s->parsed;
	while (current_token != NULL)
	{
		if (current_token->type == 9)
		printf("current token = %s\n", current_token->str);
		ft_fill_temp(s, &current_token, 0);
		if (current_token != NULL)
			current_token = current_token->next;
	}
	// while (s->parsed->command[i])
	// 	free(s->parsed->command[i++]);
	// free(s->parsed->command);
	// free(s->parsed);
	// free(s->token->str);
	// free(s->token);
	//system("leaks minishell");
	print_parsed_list(s->parsed);
}