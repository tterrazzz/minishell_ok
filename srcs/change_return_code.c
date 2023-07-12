#include "minishell.h"

void	ft_change_return_code(t_struct *s)
{
	t_envp	*return_code;

	if (!s)
		return ;
	return_code = s->envp;
	while (return_code && ft_strncmp(return_code->value[0], "?"))
		return_code = return_code->next;
	if (return_code)
	{
		if (return_code->value[1])
			ft_free_ptr((void *)return_code->value[1]);
//		return_code->value[1] = ft_itoa(s->error);
		return_code->value[1] = ft_itoa(g_error);
	}
}
