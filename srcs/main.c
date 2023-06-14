
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_struct	*s;
	char		*line;

	(void) argc;
	(void) argv;
	s = malloc(sizeof(t_struct));
	if (!s)
		return (ft_error(MALLOC, "malloc"), 1);
	ft_struct_init(s, envp);
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
	ft_free_everything(s);
	return (0);
}
