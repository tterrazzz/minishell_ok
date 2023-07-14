/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:31:54 by avan              #+#    #+#             */
/*   Updated: 2023/07/14 11:07:50 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fill_redirec(t_parsed *current_parsed, t_struct *s,
	t_token *prov, t_token **useless)
{
	t_token	*redirec_token;

	ft_node_add_back_redirec(&current_parsed, prov->type);
	redirec_token = prov->next;
	current_parsed->last_redire->filename
		= ft_strdup(redirec_token->str);
	current_parsed->last_redire->filename
		= ft_dollar_check2(s, current_parsed->last_redire->filename);
	current_parsed->last_redire->filename
		= ft_quote_check2(current_parsed->last_redire->filename, 0, 0);
	ft_node_remove_token(s, prov);
	*useless = redirec_token->next;
	ft_node_remove_token(s, redirec_token);
}

static char	**ft_extract_command(t_token *begin, t_token **current_token,
	int count, t_token *prov)
{
	char	**command;
	int		i;

	command = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	if (begin)
		*current_token = begin;
	else
		*current_token = prov;
	while ((*current_token) != NULL && (*current_token)->type != pipex)
	{
		command[i] = ft_strdup((*current_token)->str);
		i++;
		*current_token = (*current_token)->next;
	}
	command[i] = NULL;
	return (command);
}

static void	ft_fill_parsed(t_struct *s, t_parsed *current_parsed,
	t_token **current_token, int i)
{
	t_token	*prov;
	t_token	*useless;
	t_token	*begin;

	prov = *current_token;
	begin = NULL;
	while (prov != NULL && prov->type != pipex)
	{
		if (prov->type == 2 || prov->type == 3 || prov->type == 4
			|| prov->type == 5)
		{
			ft_fill_redirec(current_parsed, s, prov, &useless);
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
	current_parsed->command = ft_extract_command(begin, current_token, i, prov);
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
		current_parsed->command = ft_dollar_check(s, current_parsed->command,
				-1, 0);
		current_parsed->command = ft_quote_check(current_parsed->command, -1,
				0, 0);
	}
	current_parsed = s->parsed;
}
