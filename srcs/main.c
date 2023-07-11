
#include "minishell.h"

int	print_error(int error_code, char *content)
{
	if (error_code == 1)
	{
		ft_printf("\033[91m%s\033[0m\n",
			"minishell: parse error, quotes are never closed");
	}
	else if (error_code == 2)
	{
		ft_printf("\033[91m%s '%s'\033[0m\n",
			"minishell: parse error, near", content);
	}
	else if (error_code == 3)
	{
		ft_printf("\033[91m%s '%s'\033[0m\n",
			"minishell: the command cannot end with",
			content);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	s;
	char		*line;

	(void) argv;
	if (argc != 1)
		ft_error(SYNTAX, "Arguments incorrects");
	ft_struct_envp(&s, envp);
	while (1)
	{
		ft_struct_init(&s);
		line = readline("minishell$ ");
		if (!ft_strncmp("exit\n", line, ft_strlen(line)))
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		add_history(line);
		ft_check_quotes(line);
			break ;
		ft_lexer(&s, line);
		ft_parsing(&s);
		//system("leaks minishell");
		//ft_free_loop(&s);
	}
	//ft_free_everything(&s);
	return (0);
}
