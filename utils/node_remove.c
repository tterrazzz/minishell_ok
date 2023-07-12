#include "../srcs/minishell.h"

static t_envp	*ft_get_underscore_node(t_struct *s)
{
	t_envp	*under_node;

	if (!s)
		return (NULL);
	under_node = s->envp;
	while (under_node)
	{
		if (!ft_strncmp("_", under_node->value[0]))
			break ;
		under_node = under_node->next;
	}
	return (under_node);
}

void	ft_node_remove_underscore(t_struct *s)
{
	t_envp	*temp;
	t_envp	*next_node;
	t_envp	*under_node;

	if (!s)
		return ;
	under_node = ft_get_underscore_node(s);
	if (!under_node)
		return ;
	temp = under_node->prev;
	next_node = under_node->next;
	if (!temp)
		s->envp = next_node;
	else if (temp)
		temp->next = next_node;
	if (next_node)
		next_node->prev = temp;
	if (s->last_envp == under_node)
		s->last_envp = temp;
	ft_free_tab((void **) under_node->value);
	ft_free_ptr((void *) under_node);
	under_node = NULL;
	ft_reassign_updated_envp_char(s);
}

void	ft_node_remove_envp(t_struct *s, t_envp *node)
{
	t_envp	*temp;
	t_envp	*next_node;

	if (!s || !node)
		return ;
	temp = node->prev;
	next_node = node->next;
	if (!temp)
		s->envp = next_node;
	else if (temp)
		temp->next = next_node;
	if (next_node)
		next_node->prev = temp;
	if (s->last_envp == node)
		s->last_envp = temp;
	ft_free_tab((void **) node->value);
	ft_free_ptr((void *) node);
	node = NULL;
}

/*static void	ft_free_redirec_content(t_redirec *redirec)
{
	if (!redirec)
		return ;
	ft_free_ptr((void *)redirec->filename);
	if (redirec->here_d_pipe_fd)
	{
		close(redirec->here_d_pipe_fd[0]);
		ft_free_ptr((void *)redirec->here_d_pipe_fd);
	}
	else if (redirec->fd)
		close(redirec->fd);
	ft_free_ptr((void *)redirec);
}

void	ft_node_remove_redirec(t_parsed *parsed, t_redirec *redirec, int fd)
{
	t_redirec	*prev_re;
	t_redirec	*next_re;
	t_redirec	*temp;

	if (!parsed || !redirec)
		return ;
	temp = ft_go_to_previous_fd(redirec);
	if (temp == NULL)
		return ;
	prev_re = temp->prev;
	next_re = temp->next;
	if (prev_re)
		prev_re->next = next_re;
	if (!prev_re)
		parsed->redirection = next_re;
	if (next_re)
		next_re->prev = prev_re;
	ft_free_redirec_content(temp);
}*/