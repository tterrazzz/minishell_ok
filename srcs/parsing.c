#include "minishell.h"

/*static void	print_parsed_list(t_parsed *parsed_list)
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
}*/

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
			ft_node_add_back_redirec(&current_parsed, prov->type);
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
	if (begin)
		*current_token = begin;
	else
		*current_token = prov;
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
	t_parsed	*temp = s->parsed;
	t_redirec	*temp_redire = s->parsed->redirection;
	while (temp)
	{
		printf("parsed->command = %s\n", temp->command[0]);
		temp_redire = temp->redirection;
		while (temp_redire)
		{
			printf("temp_redire = %p\n", temp_redire);
			if (temp_redire->filename)
				printf("temp_redire = %s\n", temp_redire->filename);
			temp_redire = temp_redire->next;
		}
		temp = temp->next;
	}
	//print_parsed_list(s->parsed);
}
