#include "minishell.h"

/*	static int ft_check_if_dir_slash checks if the char *cmd is a directory */
static int	ft_check_if_dir_slash(char *cmd, int mode)
{
	struct stat	t;
	char		*str;
	char		*stock;

	if (!cmd)
		return (0);
	str = NULL;
	stock = NULL;
	printf("ici\n");
	if (stat(cmd, &t) == 0)
	{
		if (S_ISDIR(t.st_mode))
		{
			if (mode == PARENT)
			{
				stock = ft_strjoin("minishell: ", cmd);
				str = ft_strjoin(stock, ": is a directory\n");
				write(STDERR_FILENO, str, ft_strlen(str));
				ft_free_ptr((void *) stock);
				ft_free_ptr((void *) str);
				g_error = 126;
			}
			return (0);
		}
	}
	return (1);
}

/*	int ft_check_if_slash returns 0 if it is not a directory so the child
	gets the command, otherwise, the directory is not sent to execve, at the
	same time, the parent will change the g_error value accordingly and
	write the error message */
int	ft_check_if_slash(char *cmd, int mode)
{
	int	i;
	int	slash;

	if (!cmd)
		return (0);
	slash = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i++] == '/')
			slash = 1;
	}
	if (slash)
		return (ft_check_if_dir_slash(cmd, mode));
	return (1);
}
