#include "minishell.h"

void	ft_struct_envp(t_struct *s, char **envp)
{
	t_envp	*temp;
	int		i;

	s->envp = NULL;
	if (!s)
		return ;
	i = 0;
	while (envp[i])
	{
		ft_node_add_back_envp(s);
		if (i == 0)
			temp = s->envp;
		else
			temp = temp->next;
		temp->value = ft_split(envp[i], '=');
		i++;
	}
}

/*  void ft_struct_init creates the main struct and gets the envp */
void	ft_struct_init(t_struct *s)
{
	if (!s)
		return ;
	s->token = NULL;
	s->parsed = NULL;
	s->pid = NULL;
}
