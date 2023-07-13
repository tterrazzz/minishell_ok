/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:18:48 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 20:42:24 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_old_pwd_memory(t_struct *s, t_envp *temp, char *old_pwd)
{
	if (!s || !temp)
		return ;
	if (temp->value[1])
		free(temp->value[1]);
	if (s->unset_pwd > 1)
		temp->value[1] = ft_strdup(s->old_pwd_memory);
	else
	{
		temp->value[1] = old_pwd;
		temp->nb_words = 2;
	}
	if (!old_pwd && s->unset_pwd == 1)
		s->unset_pwd += 1;
}

void	ft_check_old_pwd(t_struct *s, char *old_pwd)
{
	t_envp	*temp;
	char	**value;

	if (!s)
		return ;
	temp = s->envp;
	value = NULL;
	while (temp)
	{
		if (!ft_strncmp("OLDPWD", temp->value[0]))
		{
			ft_set_old_pwd_memory(s, temp, old_pwd);
			return ;
		}
		temp = temp->next;
	}
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("OLDPWD");
	value[1] = old_pwd;
	value[2] = NULL;
	ft_node_add_back_envp(s, value, 2);
}

static void	ft_change_old_pwd2(t_struct *s, char *old_pwd)
{
	if (!s || !old_pwd)
		return ;
	if (s->unset_oldpwd == 0)
	{
		ft_check_old_pwd(s, old_pwd);
		ft_reassign_updated_envp_char(s);
	}
}

static void	ft_change_old_pwd(t_struct *s, char *new_pwd)
{
	t_envp	*temp;
	char	*old_pwd;

	if (!s)
		return ;
	temp = s->envp;
	old_pwd = NULL;
	while (temp)
	{
		if (!ft_strncmp("PWD", temp->value[0]))
		{
			old_pwd = temp->value[1];
			temp->value[1] = new_pwd;
			if (!(s->unset_oldpwd))
				ft_check_old_pwd(s, old_pwd);
			ft_reassign_updated_envp_char(s);
			return ;
		}
		temp = temp->next;
	}
	if (!temp)
		free(new_pwd);
	ft_change_old_pwd2(s, old_pwd);
}

void	ft_change_pwd(t_struct *s, char *new_pwd)
{
	t_envp	*temp;

	if (!s || !new_pwd)
		return ;
	temp = s->envp;
	if (s->pwd_memory)
	{
		if (s->old_pwd_memory)
		{
			ft_free_ptr((void *)s->old_pwd_memory);
			s->old_pwd_memory = NULL;
		}
		s->old_pwd_memory = s->pwd_memory;
	}
	s->pwd_memory = ft_strdup(new_pwd);
	ft_change_old_pwd(s, new_pwd);
}
