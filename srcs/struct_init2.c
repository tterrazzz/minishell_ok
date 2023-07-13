/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:11:03 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:11:05 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	char **ft_get_path_envp_tab gets the envp node that contains
	the name "PATH=" */
char	**ft_get_path_envp_tab(t_envp *envp)
{
	t_envp	*temp_envp;
	char	**path_tab;

	if (!envp)
		return (NULL);
	temp_envp = envp;
	path_tab = NULL;
	while (temp_envp && ft_strncmp(temp_envp->value[0], "PATH"))
		temp_envp = temp_envp->next;
	if (temp_envp && temp_envp->value && temp_envp->value[1])
		path_tab = ft_split_add_slash(temp_envp->value[1]);
	return (path_tab);
}

/*	void ft_signal_init changes the behavior of SIGINT and SIGQUIT, it also
	changes the termios */
void	ft_signal_init(t_struct *s)
{
	struct termios	saved;

	if (!s)
		return ;
	dup2(s->fd_in_saved, STDIN_FILENO);
	dup2(s->fd_out_saved, STDOUT_FILENO);
	dup2(s->fd_err_saved, STDERR_FILENO);
	tcgetattr(STDIN_FILENO, &(saved));
	s->termios = saved;
	s->termios.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &(s->termios));
	signal(SIGINT, &ft_signal_handler);
	signal(SIGQUIT, &ft_signal_handler);
}
