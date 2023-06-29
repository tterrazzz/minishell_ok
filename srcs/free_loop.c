#include "minishell.h"
static void	ft_free_token(t_struct *s)
{
	t_token	*temp;

	while (s->token)
	{
		temp = s->token->next;
		if (s->token->str != NULL)
			free(s->token->str);
		free(s->token);
		s->token = temp;
	}
}

void	ft_free_loop(t_struct *s)
{
	ft_free_token(s);
}