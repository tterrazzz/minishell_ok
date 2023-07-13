/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:33:51 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:33:52 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_nb_nodes_envp(t_struct *s)
{
	t_envp	*temp;
	int		nb_nodes;

	if (!s)
		return (0);
	nb_nodes = 0;
	temp = s->envp;
	while (temp)
	{
		if (ft_strncmp("?", temp->value[0]) && ft_strncmp("_",
				temp->value[0]))
			nb_nodes++;
		temp = temp->next;
	}
	return (nb_nodes);
}

int	ft_check_first_arg(t_struct *s, t_parsed *parsed)
{
	char	*str;

	if (!s || !parsed)
		return (0);
	str = parsed->command[1];
	if (str[0] == '-')
	{
		if ((str[1] == '-' && !str[2]) || !str[1])
		{
			if (parsed->command[2])
				return (1);
			else if (!str[1])
				return (1);
			else
				return (ft_print_envp_ascii_order(s), 0);
		}
		else
			return (ft_error_export(s, str, INVALID_OPTION), 0);
	}
	return (1);
}

int	ft_export(t_struct *s, t_parsed *parsed)
{
	char	**name_value;
	int		i;

	if (!s || !parsed)
		return (1);
	i = 1;
	name_value = NULL;
	if (!(parsed->command[i]))
		ft_print_envp_ascii_order(s);
	else
	{
		if (!ft_check_first_arg(s, parsed))
			return (0);
		while (parsed->command[i])
		{
			ft_check_args(s, parsed, parsed->command[i]);
			i++;
		}
		ft_reassign_updated_envp_char(s);
	}
	return (0);
}
