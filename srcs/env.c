/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:33:17 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:33:18 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_struct *s)
{
	t_envp	*temp;

	if (!s)
		return (1);
	temp = s->envp;
	while (temp)
	{
		if (temp->nb_words == 2)
		{
			write(STDOUT_FILENO, temp->value[0], ft_strlen(temp->value[0]));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, temp->value[1], ft_strlen(temp->value[1]));
			write(STDOUT_FILENO, "\n", 1);
		}
		temp = temp->next;
	}
	return (0);
}
