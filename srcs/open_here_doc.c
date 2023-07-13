/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:03:50 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:03:50 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	static void ft_child_process_hd writes from the STDIN_FILENO to the
	redirection hd_pipe_fd */
static void	ft_child_process_hd(t_struct *s, t_redirec *re)
{
	char	*line;

	if (!s || !re)
		return ;
	signal(SIGINT, &ft_heredoc_handler);
	close(re->here_d_pipe_fd[0]);
	while (1)
	{
		ft_ctrl_remove(1);
		line = readline("> ");
		ft_ctrl_remove(0);
		if (line == NULL || !(ft_strncmp(re->filename, line)))
		{
			ft_free_ptr((void *)line);
			break ;
		}
		line = ft_dollar_check2(s, line);
		write(re->here_d_pipe_fd[1], line, ft_strlen(line));
		write(re->here_d_pipe_fd[1], "\n", 1);
		ft_free_ptr((void *)line);
	}
	close(re->here_d_pipe_fd[1]);
	exit(0);
}

static int	ft_parent_process_hd(t_parsed *parsed, t_redirec *redi)
{
	int	error;

	if (!parsed || !redi)
		return (1);
	close(redi->here_d_pipe_fd[1]);
	waitpid(redi->pid, &error, 0);
	if (error != 0)
	{
		g_st.error = 1;
		return (1);
	}
	if (parsed->here_d_pipe_fd && parsed->here_d_pipe_fd[0])
		close(parsed->here_d_pipe_fd[0]);
	parsed->here_d_pipe_fd = redi->here_d_pipe_fd;
	return (0);
}

/*	static int ft_pipe_and_fork_hd calls a child process and wait it to end 
	and sets the parsed->here_d_pipe_fd to the newly setup redirection->
	here_d_pipe_fd */
static int	ft_pipe_and_fork_hd(t_struct *s, t_parsed *parsed, t_redirec *redi)
{
	if (!parsed || !redi)
		return (1);
	redi->here_d_pipe_fd = malloc(sizeof(int) * 2);
	if (!(redi->here_d_pipe_fd))
		return (ft_error(s, MALLOC, "malloc"), 1);
	if (pipe(redi->here_d_pipe_fd) < 0)
		return (ft_error(s, PIPE, "pipe"), 1);
	redi->pid = fork();
	signal(SIGINT, &ft_doing_nothing);
	signal(SIGQUIT, &ft_doing_nothing);
	if (redi->pid < 0)
		return (ft_error(s, FORK, "fork"), 1);
	if (redi->pid == 0)
		ft_child_process_hd(s, redi);
	if (ft_parent_process_hd(parsed, redi))
		return (1);
	return (0);
}

/*	int ft_open_double_redirect_in_one_parsed opens all the
	double_redirection_in in one parsed struct */
int	ft_open_double_redirect_in_one_parsed(t_struct *s, t_parsed *parsed)
{
	t_redirec	*temp_redirec;

	if (!parsed)
		return (0);
	temp_redirec = parsed->redirection;
	while (temp_redirec)
	{
		if (temp_redirec->type == double_redirect_in)
		{
			if (ft_pipe_and_fork_hd(s, parsed, temp_redirec))
				return (1);
		}
		if (temp_redirec->next == NULL)
			break ;
		temp_redirec = temp_redirec->next;
	}
	return (0);
}

/*	int ft_open_double_redirect_in opens all the double_redirection_in and
	gets the last one as the one to use per parsed struct, it then closes all
	the others on the read side [0] opened before, and it does it
	for every parsed struct */
int	ft_open_double_redirect_in(t_struct *s, t_parsed *parsed)
{
	t_parsed	*temp_parsed;

	if (!s || !parsed)
		return (1);
	temp_parsed = parsed;
	while (temp_parsed)
	{
		if (ft_open_double_redirect_in_one_parsed(s, temp_parsed))
			return (1);
		temp_parsed = temp_parsed->next;
	}
	return (0);
}
