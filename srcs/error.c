#include "minishell.h"

/*  static void ft_functions_error takes care of the error message for pipe,
	fork or malloc failures */
static void	ft_functions_error(int error)
{
	if (error == SYNTAX)
		write(STDERR_FILENO, "syntax error\n", 13);
	else if (error == PIPE)
		write(STDERR_FILENO, "pipe failed\n", 12);
	else if (error == FORK)
		write(STDERR_FILENO, "fork failed\n", 12);
	else if (error == MALLOC)
		write(STDERR_FILENO, "malloc failed\n", 14);
	else if (error == ARGC)
		write(STDERR_FILENO, "No arguments accepted\n", 22);
}

/*	static void ft_exec_error writes the error message dedicated to
	the execve or the opening of a file */
static void	ft_exec_error(t_struct *s, int error, char *name, char *str)
{
	char	*stock;

	if (!s || !name)
		return ;
	stock = NULL;
	if (error == EXECVE)
	{
		stock = ft_strjoin("minishell: ", name);
		if (ft_strnstr(name, "/", ft_strlen(name)) || !(s->path_tab))
			str = ft_strjoin(stock, ": No such file or directory\n");
		else
			str = ft_strjoin(stock, ": command not found\n");
		write(STDERR_FILENO, str, ft_strlen(str));
	}
	else if (error == FIILE)
	{
		stock = ft_strjoin("minishell: ", name);
		if (errno == EACCES)
			str = ft_strjoin(stock, ": Permission denied\n");
		else if (errno == ENOENT)
			str = ft_strjoin(stock, ": No such file or directory\n");
		write(STDERR_FILENO, str, ft_strlen(str));
	}
	ft_free_ptr((void *)stock);
	ft_free_ptr((void *)str);
}

/*  ft_error sends the right error message to the stderror (2) */
void	ft_error(t_struct *s, int error, char *name)
{
	char	*str;

	if (!name)
		return ;
	str = NULL;
	if (error == SYNTAX || error == PIPE || error == FORK || error == MALLOC
		|| error == ARGC)
		ft_functions_error(error);
	else if (error == EXECVE || error == FIILE)
		ft_exec_error(s, error, name, NULL);
}

void	ft_error_env(t_struct *s, char *name)
{
	char	*stock;
	char	*str;

	if (!s)
		return ;
	stock = ft_strjoin("env: ", name);
	str = ft_strjoin(stock, ": No such file or directory\n");
	ft_free_ptr((void *)stock);
	write(STDERR_FILENO, str, ft_strlen(str));
	ft_free_ptr((void *)str);
}

/*	void ft_error_code gets the number of the execve */
void	ft_error_code(int error_last_cmd)
{
	if (WIFSIGNALED(error_last_cmd))
	{
		if (WTERMSIG(error_last_cmd) == SIGINT)
			g_st.error = 130;
		else if (WTERMSIG(error_last_cmd) == SIGQUIT)
			g_st.error = 131;
		else if (WTERMSIG(error_last_cmd) == SIGSEGV)
			g_st.error = 139;
	}
}
