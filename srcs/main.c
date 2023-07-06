
#include "minishell.h"

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
		ft_lexer(&s, line);
		ft_parsing(&s);
		//system("leaks minishell");
		//ft_free_loop(&s);
	}
	ft_free_everything(&s);
	return (0);
}
