#include "minishell.h"

/*	void ft_get_files_index_order gets the redirec struct
	that we want to get with *i */
/*void	ft_get_files_index_order(t_redirec *index_redirec, int *i)
{
	if (!index_redirec)
		return ;
	while (*i != index_redirec->index)	
	{
		while (index_redirec->prev)
		{
			if (*i == index_redirec->index)
				return ;
			index_redirec = index_redirec->prev;
		}
		while (index_redirec->next)
		{
			if (*i == index_redirec->index)
				return ;
			index_redirec = index_redirec->next;
		}
	}
}*/

void	ft_open_files_inside_pipe(t_parsed *index_parsed)
{
	int	open_fd_in_temp;
	int	i;

	i = 0;
	while (i < index_parsed->nb_redirect)
	{
		ft_get_right_index_order(index_parsed->redirection, &i);




		open_fd_in_temp = open(s->parsed->redirection_in->filename, O_RDONLY);
		if (open_fd_in_temp == -1)
		{
			ft_error(s, FIILE, s->parsed->redirection_in[i]);
			index_parsed->error = INFILE_PERMISSION_DENIED;
			return;
		}
		if (i == index_parsed->nb_redirection_in - 1)
			index_parsed->fd_in = open_fd_in_temp;
		i++;
	}
}

/*	void ft_open_files_get_fds opens all files (in and out) in the right order until
	we do not have permission.
	if every redirection_in can be opened, it stores the last one's fd_in, same for
	the redirection_out, it stores the last one's fd_out */
void	ft_open_files_get_fds(t_struct *s)
{
	t_parsed	*index_parsed;

	if (!s)
		return ;
	/* if redirections_in */
	index_parsed = s->parsed;
	while (index_parsed)
	{
		ft_open_files_inside_pipe(index_parsed);
		index_parsed = index_parsed->next;
	}

	/* if redirections_out */

	/* get the last redirections_out to fd */
}