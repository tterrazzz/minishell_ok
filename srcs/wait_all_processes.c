/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:08:01 by avan              #+#    #+#             */
/*   Updated: 2023/07/15 11:23:43 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	static void ft_error_code_env_pwd gets the error_code from the env, pwd
	pipeline if there is one, it would be executed in the child process so
	we need this function to be run in the parent process */
static void	ft_error_code_env_pwd(t_struct *s, t_parsed *parsed)
{
	char	*str;
	char	*str2;
	char	*cmd;
	int		i;

	if (!s || !parsed)
		return ;
	cmd = parsed->command[0];
	str = parsed->command[1];
	str2 = parsed->command[2];
	i = 0;
	while (str[i] == '-')
		i++;
	if (i > 0 && i != (int) ft_strlen(str))
		g_st.error = 1;
	else if (ft_strncmp(cmd, "pwd") && i == (int) ft_strlen(str)
		&& str2 && !ft_check_access(s->path_tab, str2))
		g_st.error = 127;
	else if (ft_strncmp(cmd, "pwd") && i == 0
		&& !ft_check_access(s->path_tab, parsed->command[1]))
		g_st.error = 127;
}

void	ft_get_last_cmd_code2(t_parsed *parsed, char *cmd)
{
	if (!parsed || !cmd)
		return ;
	if (!ft_strncmp(".", cmd))
		g_st.error = 2;
	else if (!ft_strncmp("..", cmd))
		g_st.error = 127;
}

/*	void ft_get_last_cmd_code will check the access of the last command
	and gets parsed->error and s->error to 127 */
void	ft_get_last_cmd_code(t_struct *s, t_parsed *parsed)
{
	char	*temp;
	char	*cmd;

	if (!s || !parsed || (parsed && !(parsed->command)))
		return ;
	cmd = parsed->command[0];
	if ((!ft_strncmp(cmd, "pwd") || !ft_strncmp(cmd, "env"))
		&& parsed->command[1])
		ft_error_code_env_pwd(s, parsed);
	else
	{
		temp = ft_check_access(s->path_tab, cmd);
		if (temp == NULL && (ft_strncmp(cmd, "cd") && ft_strncmp(cmd, "exit")
				&& ft_strncmp(cmd, "unset") && ft_strncmp(cmd, "export")
				&& ft_strncmp(cmd, "env") && ft_strncmp(cmd, "pwd")))
		{
			if (cmd)
			{
				parsed->error = 127;
				g_st.error = 127;
			}
		}
		ft_get_last_cmd_code2(parsed, cmd);
		ft_free_ptr((void *) temp);
	}
}

/*	void ft_wait_all_processes waits for all child processes to finish and
	will check if the last command did not have problem, if options are not
	authorized but the command is accessible, s->error will be 1 */
void	ft_wait_all_processes(t_struct *s)
{
	t_parsed	*temp_parsed;
	int			error;
	int			error_last_cmd;

	if (!s)
		return ;
	temp_parsed = s->parsed;
	while (temp_parsed->next)
	{
		waitpid(temp_parsed->pid, &error, 0);
		temp_parsed = temp_parsed->next;
	}
	waitpid(temp_parsed->pid, &error_last_cmd, 0);
	if ((ft_strncmp(temp_parsed->command[0], "..")
			&& ft_strncmp(temp_parsed->command[0], ".")
			&& ft_check_if_slash(temp_parsed->command[0], CHILD)
			&& !ft_last_is_builtin(temp_parsed))
		|| (!(temp_parsed->command[0])))
		g_st.error = error_last_cmd % 255;
	ft_error_code(error_last_cmd);
}
