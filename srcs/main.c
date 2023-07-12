
#include "minishell.h"

int	g_error = 0;

int	print_error(t_struct *s, int error_code, char *content)
{
	if (!s)
		return (0);
	if (error_code == 1)
	{
		ft_printf("\033[91m%s\033[0m\n",
			"minishell: parse error quotes are never closed");
		g_error = 1;
	}
	else if (error_code == 2)
	{
		ft_printf("\033[91m%s '%s'\033[0m\n",
			"minishell: syntax error near unexpected token", content);
		g_error = 258;
	}
	else if (error_code == 3)
	{
		ft_printf("\033[91m%s\033[0m\n",
			"minishell: syntax error");
		g_error = 1;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	s;
	char		*line;

	(void) argc;
	(void) argv;
	if (argc != 1)
		ft_error(&s, SYNTAX, "Arguments incorrects");
	ft_struct_init(&s, envp);
	while (1)
	{
		ft_signal_init(&s);
		signal(SIGINT, &ft_signal_handler);
		signal(SIGQUIT, &ft_signal_handler);
//		ft_ctrl_remove(1);
		line = readline("minishell$ ");
//		ft_ctrl_remove(0);
		add_history(line);
		if (ft_check_quotes(&s, line))
			continue ;
		ft_lexer(&s, line);
		if (ft_norminette(&s))
			continue ;
		ft_parsing(&s);
		if (line != NULL)
			ft_exec(&s);
		else
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(0);
		}
		printf("node [?] = %s\n", ft_get_env_value(&s, "?"));
		ft_free_structs(&s);
		free(line);
		line = NULL;
		system("leaks minishell");
		//system("leaks minishell");
	}
	close(s.fd_in_saved);
	close(s.fd_out_saved);
	ft_free_everything(&s, 0);
	return (0);
}
