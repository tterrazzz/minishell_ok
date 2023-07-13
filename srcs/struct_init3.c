/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:08:12 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:08:13 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_oldpwd_envp(t_struct *s)
{
	char	**value;

	if (!s)
		return ;
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("OLDPWD");
	value[1] = NULL;
	value[2] = NULL;
	ft_node_add_back_envp(s, value, 1);
}

void	ft_create_pwd_envp(t_struct *s)
{
	char	**value;
	char	*current_path;

	if (!s)
		return ;
	current_path = getcwd(NULL, 4096 + 1);
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("PWD");
	value[1] = ft_strdup(current_path);
	value[2] = NULL;
	ft_free_ptr((void *)current_path);
	ft_node_add_back_envp(s, value, 2);
}

void	ft_create_shlvl_envp(t_struct *s)
{
	char	**value;

	if (!s)
		return ;
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("SHLVL");
	value[1] = ft_strdup("1");
	value[2] = NULL;
	ft_node_add_back_envp(s, value, 2);
}

/*	void ft_create_environment creates a small environment if there is no
	environement at the beginning, only variables are PWD, SHLVL,
	? and OLDPWD */
void	ft_create_environment(t_struct *s)
{
	char	**value;

	if (!s)
		return ;
	ft_create_pwd_envp(s);
	ft_create_shlvl_envp(s);
	ft_create_oldpwd_envp(s);
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("?");
	value[1] = ft_strdup("0");
	value[2] = NULL;
	ft_node_add_back_envp(s, value, 0);
}
