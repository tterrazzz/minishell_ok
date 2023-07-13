/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:33:32 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:33:35 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	char *ft_get_env_value returns the value for the env name value given
	or NULL if it does not find it */
char	*ft_get_env_value(t_struct *s, char *env_name)
{
	char	*env_value;
	t_envp	*t;

	if (!env_name)
		return (NULL);
	env_value = NULL;
	t = s->envp;
	while (t)
	{
		if (!ft_strcmp(t->value[0], env_name))
		{
			env_value = t->value[1];
			break ;
		}
		t = t->next;
	}
	return (env_value);
}

/*	char *ft_env_exists gets the name of the variable we want, it checks the
	envp list and returns the address of the name if it finds it, it returns
	NULL if not */
char	*ft_env_exists(t_envp *envp_list, char *env_name)
{
	char	*env_value;
	t_envp	*t;

	if (!envp_list || !env_name)
		return (NULL);
	env_value = NULL;
	t = envp_list;
	while (t)
	{
		if (!ft_strncmp(t->value[0], env_name))
		{
			env_value = t->value[0];
			break ;
		}
		t = t->next;
	}
	return (env_value);
}
