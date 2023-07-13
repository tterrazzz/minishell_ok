/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:04:27 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:04:28 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	void ft_free_tab frees a pointer of pointer */
void	ft_free_tab(void **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		ft_free_ptr((void *)tab[i]);
		i++;
	}
	free(tab);
}

static void	ft_free_envp(t_struct *s)
{
	t_envp	*temp;

	if (!s)
		return ;
	temp = s->envp;
	while (temp)
	{
		ft_free_tab((void **)temp->value);
		ft_free_ptr((void *)temp->prev);
		s->envp = temp->next;
		if (!temp->next)
		{
			ft_free_ptr((void *)temp);
			return ;
		}
		temp = s->envp;
	}
}

void	ft_free_token(t_struct *s)
{
	t_token	*temp;

	if (!s)
		return ;
	temp = s->token;
	while (temp)
	{
		ft_free_ptr((void *)temp->str);
		ft_free_ptr((void *)temp->prev);
		s->token = temp->next;
		if (!temp->next)
		{
			ft_free_ptr((void *)temp);
			return ;
		}
		temp = s->token;
	}
}

void	ft_free_structs(t_struct *s)
{
	if (!s)
		return ;
	if (s->token)
		ft_free_token(s);
	if (s->parsed)
		ft_free_parsed(s);
	s->i = 0;
	s->j = 0;
	g_st.error = 0;
}

/*  void ft_free_everything frees everything, if mode == 1, even the structs */
void	ft_free_everything(t_struct *s, int mode)
{
	if (!s)
		return ;
	if (mode == 1)
		ft_free_structs(s);
	ft_free_envp(s);
	ft_free_tab((void **)s->envp_char);
	ft_free_ptr((void *)s->pipe_fd);
	ft_free_tab((void **)s->path_tab);
	ft_free_ptr((void *)s->old_pwd_memory);
	ft_free_ptr((void *)s->pwd_memory);
	ft_free_ptr((void *)s);
}
