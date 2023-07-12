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
