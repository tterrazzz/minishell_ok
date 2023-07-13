/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:08:28 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:08:28 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_next_token_space(t_struct *s, t_token *tok)
{
	t_token		*current_token;

	current_token = tok;
	current_token = current_token->next;
	if (!current_token)
	{
		print_error(s, 2, "newline");
		return (1);
	}
	return (0);
}

static int	ft_check_next_token(t_struct *s, t_token *tok)
{
	t_token	*current_token;

	current_token = tok;
	current_token = current_token->next;
	if (!current_token)
	{
		print_error(s, 2, "newline");
		return (1);
	}
	if (current_token->type == 2 || current_token->type == 3
		|| current_token->type == 4 || current_token->type == 5
		|| current_token->type == 1)
	{
		print_error(s, 2, current_token->str);
		return (1);
	}
	return (0);
}

int	ft_norminette(t_struct *s)
{
	t_token		*current_token;
	int			i;
	int			error;

	current_token = s->token;
	i = 0;
	error = 0;
	while (current_token != NULL)
	{
		if (current_token->type == 1 && i == 0)
			error = print_error(s, 2, "|");
		else if (current_token->type == 1)
			error = ft_check_next_token_space(s, current_token);
		else if (current_token->type == 2 || current_token->type == 3
			|| current_token->type == 4 || current_token->type == 5)
			error = ft_check_next_token(s, current_token);
		if (error != 0)
			return (ft_change_return_code(s), ft_free_token(s), error);
		current_token = current_token->next;
		i++;
	}
	return (error);
}
