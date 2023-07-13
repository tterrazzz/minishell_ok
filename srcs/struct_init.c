#include "minishell.h"

static void	ft_check_basic_env(t_struct *s, int old_pwd, int pwd, int shlvl)
{
	t_envp	*temp;

	if (!s)
		return ;
	temp = s->envp;
	while (temp)
	{
		if (!ft_strncmp(temp->value[0], "OLDPWD"))
			old_pwd = 1;
		else if (!ft_strncmp(temp->value[0], "PWD"))
			pwd = 1;
		else if (!ft_strncmp(temp->value[0], "SHLVL"))
			shlvl = 1;
		temp = temp->next;
	}
	if (!old_pwd)
		ft_create_oldpwd_envp(s);
	if (!pwd)
		ft_create_pwd_envp(s);
	if (!shlvl)
		ft_create_shlvl_envp(s);
}

/*	static void ft_read_and_create_envp reads the existing environment and
	creates the envp list */
static void	ft_read_and_create_envp(t_struct *s, char **envp)
{
	int	i;
	int	j;
	int	temp;

	if (!s || !envp)
		return ;
	i = -1;
	j = 0;
	temp = 0;
	while (envp[++i])
	{
		if (!ft_strncmp_length("?=", envp[i], 2) && envp[i])
			ft_node_add_back_envp(s, ft_split_envp(envp[i], &j), 0);
		else if (envp[i])
			ft_node_add_back_envp(s, ft_split_envp(envp[i], &j), j);
		if (!ft_strncmp_length("SHLVL=", envp[i], 6))
		{
			temp = ft_atoi(ft_get_env_value(s, "SHLVL"));
			free(s->last_envp->value[1]);
			s->last_envp->value[1] = ft_itoa(temp + 1);
		}
	}
	ft_check_basic_env(s, 0, 0, 0);
	return ;
}

void	ft_check_return_code_node(t_struct *s)
{
	t_envp	*return_code;
	char	**value;

	if (!s)
		return ;
	value = NULL;
	return_code = s->last_envp;
	while (return_code)
	{
		if (!ft_strncmp(return_code->value[0], "?"))
			return ;
		return_code = return_code->prev;
	}
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("?");
	value[1] = ft_strdup("0");
	value[2] = NULL;
	ft_node_add_back_envp(s, value, 0);
}

/*	static void ft_struct_envp gets the envp and splits the lines into
	two char *str, each envp node gets its char **value */
static void	ft_struct_envp(t_struct *s, char **envp)
{
	if (!s || !envp)
		return ;
	if (!(*envp))
		return (ft_create_environment(s));
	ft_read_and_create_envp(s, envp);
	ft_check_return_code_node(s);
}

/*  void ft_struct_init creates the main struct and gets the envp */
void	ft_struct_init(t_struct *s, char **envp)
{
	if (!s)
		return ;
	s->envp = NULL;
	s->token = NULL;
	s->parsed = NULL;
	ft_struct_envp(s, envp);
	s->path_tab = ft_get_path_envp_tab(s->envp);
	s->fd_in_saved = dup(STDIN_FILENO);
	s->fd_out_saved = dup(STDOUT_FILENO);
	s->fd_err_saved = dup(STDERR_FILENO);
	s->pipe_fd = malloc(sizeof(int) * 2);
	if (!(s->pipe_fd))
		return (ft_error(s, MALLOC, "malloc"));
	s->old_pwd_memory = NULL;
	s->pwd_memory = NULL;
	s->unset_oldpwd = 0;
	s->unset_pwd = 0;
	s->i = 0;
	s->j = 0;
	s->error = 0;
	s->envp_char = ft_envp_list_to_tab_string(s->envp);
	g_st.signal = 0;
}
