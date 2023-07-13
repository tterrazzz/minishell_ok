/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:09:12 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 19:48:19 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

static t_envp	*ft_get_underscore_node(t_struct *s)
{
	t_envp	*under_node;

	if (!s)
		return (NULL);
	under_node = s->envp;
	while (under_node)
	{
		if (!ft_strncmp("_", under_node->value[0]))
			break ;
		under_node = under_node->next;
	}
	return (under_node);
}

void	ft_node_remove_underscore(t_struct *s)
{
	t_envp	*temp;
	t_envp	*next_node;
	t_envp	*under_node;

	if (!s)
		return ;
	under_node = ft_get_underscore_node(s);
	if (!under_node)
		return ;
	temp = under_node->prev;
	next_node = under_node->next;
	if (!temp)
		s->envp = next_node;
	else if (temp)
		temp->next = next_node;
	if (next_node)
		next_node->prev = temp;
	if (s->last_envp == under_node)
		s->last_envp = temp;
	ft_free_tab((void **) under_node->value);
	ft_free_ptr((void *) under_node);
	under_node = NULL;
	ft_reassign_updated_envp_char(s);
}

void	ft_node_remove_envp(t_struct *s, t_envp *node)
{
	t_envp	*temp;
	t_envp	*next_node;

	if (!s || !node)
		return ;
	temp = node->prev;
	next_node = node->next;
	if (!temp)
		s->envp = next_node;
	else if (temp)
		temp->next = next_node;
	if (next_node)
		next_node->prev = temp;
	if (s->last_envp == node)
		s->last_envp = temp;
	ft_free_tab((void **) node->value);
	ft_free_ptr((void *) node);
	node = NULL;
}

void	ft_node_remove_token(t_struct *s, t_token *node)
{
	t_token	*temp;
	t_token	*next_node;

	if (!s || !node)
		return ;
	temp = node->prev;
	next_node = node->next;
	if (!temp)
		s->token = next_node;
	else if (temp)
		temp->next = next_node;
	if (next_node)
		next_node->prev = temp;
	free(node->str);
	free(node);
	node = NULL;
}
