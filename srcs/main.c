
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void) argc;
	(void) argv;
	(void) envp;
	while (1)
	{
		line = readline("minishell% ");
		if (line == NULL || !ft_strncmp("exit\n", line, ft_strlen(line)))
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		add_history(line);
		free(line);
	}
	return (0);
}
