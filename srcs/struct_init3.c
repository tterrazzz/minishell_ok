#include "minishell.h"

/*	static void ft_create_environement2 creates the OLDPWD and ? nodes when
	there is no existing environment */
static void	ft_create_environment2(t_struct *s, char **value, char **value2)
{
	if (!s)
		return ;
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("OLDPWD");
	value[1] = NULL;
	value[2] = NULL;
	ft_node_add_back_envp(s, value, 1);
	value2 = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value2[0] = ft_strdup("?");
	value2[1] = ft_strdup("0");
	value2[2] = NULL;
	ft_node_add_back_envp(s, value2, 0);
}

/*	void ft_create_environment creates a small environment if there is no
	environement at the beginning, only variables are PWD, SHLVL,
	? and OLDPWD */
void	ft_create_environment(t_struct *s, char **value2)
{
	char	**value;
	char	*current_path;

	if (!s)
		return ;
	current_path = getcwd(NULL, 4096 + 1);
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("PWD");
	value[1] = ft_strdup(current_path);
	value[2] = NULL;
	ft_free_ptr((void *)current_path);
	ft_node_add_back_envp(s, value, 2);
	value2 = malloc(sizeof(char *) * (2 + 1));
	if (!value2)
		return ;
	value2[0] = ft_strdup("SHLVL");
	value2[1] = ft_strdup("1");
	value2[2] = NULL;
	ft_node_add_back_envp(s, value2, 2);
	ft_create_environment2(s, NULL, NULL);
}
