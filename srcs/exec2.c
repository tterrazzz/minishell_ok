/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:08:07 by avan              #+#    #+#             */
/*   Updated: 2023/07/15 11:34:50 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  char *ft_check_access gets the command name and the envp linked list, with
	each node containing all the seperated environment variable name with
	their value, except PATH that gets all of its paths terminated with '/'
	and returns the accessible path for the command */
char	*ft_check_access(char **path_tab, char *cmd_name)
{
	char	*stock;
	char	*path_accessible;
	int		i;

	if (!path_tab || !cmd_name)
		return (NULL);
	stock = NULL;
	path_accessible = NULL;
	i = 1;
	while (path_tab[i])
	{
		stock = ft_strjoin(path_tab[i], cmd_name);
		if (!access(stock, X_OK))
		{
			path_accessible = stock;
			break ;
		}
		free(stock);
		i++;
	}
	return (path_accessible);
}

static void	ft_execution3(t_struct *s, t_parsed *parsed)
{
	if (!s || !parsed)
		return ;
	execve(parsed->command[0], parsed->command, s->envp_char);
	parsed->path = ft_check_access(s->path_tab, parsed->command[0]);
	if (execve(parsed->path, parsed->command, s->envp_char) < 0)
		ft_error(EXECVE, parsed->command[0]);
	if (!ft_check_if_slash(parsed->command[0], 0))
		exit(127);
}

static void	ft_execution2(t_struct *s, t_parsed *parsed)
{
	if (!s || !parsed)
		return ;
	if (ft_strncmp("..", parsed->command[0])
		&& access(parsed->command[0], R_OK))
	{
		if (errno != EACCES)
			parsed->path = ft_check_access(s->path_tab, parsed->command[0]);
		if (parsed->path && (execve(parsed->path, parsed->command,
					s->envp_char) < 0))
			ft_error(EXECVE, parsed->command[0]);
		else
		{
			ft_error(EXECVE, parsed->command[0]);
			if (errno == EACCES)
				exit(126);
			else if (errno == ENOENT)
				exit(127);
		}
	}
	else
		ft_execution3(s, parsed);
}

/*	void ft_execution tries to execute the absolute path, if it does not work,
	it tries all the relative paths */
void	ft_execution(t_struct *s, t_parsed *parsed)
{
	int	built_in_child;

	if (!s || !parsed)
		return ;
	built_in_child = ft_find_built_in(s, parsed);
	if (built_in_child)
	{
		if (built_in_child == 2)
		{
			execve(parsed->command[s->i], &(parsed->command[s->i]),
				s->envp_char);
			parsed->path = ft_check_access(s->path_tab, parsed->command[s->i]);
			if (execve(parsed->path, &(parsed->command[s->i]), s->envp_char))
				ft_error_env(parsed->command[s->i]);
		}
		else
			ft_execution2(s, parsed);
	}
	ft_free_everything(s, 1);
	exit(0);
}
