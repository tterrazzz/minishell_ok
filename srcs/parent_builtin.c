/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:07:45 by avan              #+#    #+#             */
/*   Updated: 2023/07/15 10:35:17 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	void ft_env_changing_builtin is called in the parent process right after
	forking, it will process to execute the builtin if it changes the
	environment, on the other side, in the child process, the ft_find_built_in
	function will not execute it */
void	ft_env_changing_builtin(t_struct *s, t_parsed *parsed)
{
	char	*cmd;

	if (!s || !parsed)
		return ;
	cmd = NULL;
	if (parsed->command)
		cmd = parsed->command[0];
	if (!ft_strncmp(cmd, "cd"))
		ft_cd(s, parsed);
	else if (!ft_strncmp(cmd, "exit"))
		ft_exit(s, parsed);
	else if (!ft_strncmp(cmd, "unset"))
		ft_unset(s, parsed);
	else if (parsed->command && parsed->command[0] && parsed->command[1]
		&& !ft_strncmp(cmd, "export") && !(parsed->prev) && !(parsed->next))
		ft_export(s, parsed);
	else if (!ft_strncmp(cmd, "."))
		ft_dot();
	else
		ft_check_if_slash(cmd, PARENT);
}

/*	int ft_last_is_builtin checks if the command from the last pipeline is
	a builtin, so that we check the error_codes and not from execve */
int	ft_last_is_builtin(t_parsed *parsed)
{
	char	*cmd;

	if (!parsed)
		return (0);
	cmd = NULL;
	if (parsed->command)
		cmd = parsed->command[0];
	if (!ft_strncmp(cmd, "cd") || !ft_strncmp(cmd, "exit")
		|| !ft_strncmp(cmd, "unset") || (parsed->command && parsed->command[0]
			&& parsed->command[1] && !ft_strncmp(cmd, "export"))
		|| !ft_strncmp(cmd, "env") || !ft_strncmp(cmd, "pwd")
		|| !(ft_check_if_slash(cmd, CHILD)))
		return (1);
	return (0);
}
