/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:07:51 by avan              #+#    #+#             */
/*   Updated: 2023/07/15 12:09:05 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_struc	g_st;

/*	static int ft_read_line gets the signals and the prompt, then tokenize it
	and parses it */
static int	ft_read_line(t_struct *s)
{
	char	*line;

	if (!s)
		return (0);
	ft_signal_init(s);
	ft_ctrl_remove(1);
	line = readline("minishell$ ");
	ft_ctrl_remove(0);
	if (g_st.signal)
		ft_change_return_code(s);
	add_history(line);
	if (!line)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
	else if (ft_check_quotes(s, line))
		return (ft_change_return_code(s), 1);
	if (line[0] == '\0')
		return (free(line), 1);
	ft_lexer(s, line);
	if (ft_norminette(s))
		return (1);
	ft_parsing(s);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*s;

	(void) argv;
	s = malloc(sizeof(t_struct));
	if (!s)
		return (ft_error(MALLOC, "malloc"), 1);
	if (argc != 1)
		return (ft_error(ARGC, "No arguments accepted"), 1);
	ft_struct_init(s, envp);
	while (1)
	{
		if (ft_read_line(s))
			continue ;
		ft_exec(s);
		ft_change_return_code(s);
		ft_free_structs(s);
	}
	close(s->fd_in_saved);
	close(s->fd_out_saved);
	ft_free_everything(s, 0);
	return (0);
}
