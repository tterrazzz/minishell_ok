#include "minishell.h"

void	ft_error(int error, char *line)
{
	if (!line)
		return ;
	(void) line;
	if (error == MALLOC)
		write(2, "malloc failed\n", 14);
	if (error == SYNTAX)
		write(2, "syntax error\n", 13);
}