/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_add_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:51:00 by marvin            #+#    #+#             */
/*   Updated: 2023/06/05 14:08:39 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	ft_node_add_back_redirec(t_parsed *parsed, t_Tokentype type)
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
	if (!(parsed->redirection))
		parsed->redirection = last;
	if (parsed->last_redire)
	{
		last->prev = parsed->last_redire;
		parsed->last_redire->next = last;
	}
	parsed->last_redire = last;
}

void	ft_node_add_back_envp(t_struct *s)
{
	t_envp	*last;
	t_envp	*temp;

	if (!s)
		return ;
	last = malloc(sizeof(t_envp));
	if (!last)
		return ;
	last->next = NULL;
	last->value = NULL;
	if (!s->envp)
		s->envp = last;
	else
	{
		temp = s->envp;
		while (temp->next)
			temp = temp->next;
		temp->next = last;
	}
}

void	ft_node_remove_token(t_struct *s, t_token *node)
{
	t_token	*temp;
	t_token	*next_node;

	if (!s || !node)
		return ;
	temp = node->prev;
	next_node = node->next;
	// if (!temp && !next_node)
	// 	s->token = NULL;
	if (!temp)
		s->token = next_node;
	else if (temp)
		temp->next = next_node;
	if (next_node)
		next_node->prev = temp;
	// ft_free_tab((void **) node->value);
	// ft_free_ptr((void *) node);
	free(node->str);
	free(node);
	node = NULL;
}

