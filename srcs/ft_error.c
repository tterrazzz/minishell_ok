#include "minishell.h"

void	ft_parsing_error(int error)
{
	if (error == SYNTAX)
	{
		printf("Syntax error");
		exit (258);
	}
}

void    ft_error(int error, char *line)
{
	if (!line)
		return ;
	(void) line;
	if (error == MALLOC)
		write(2, "malloc failed\n", 14);
	if (error == SYNTAX)
		write(2, "syntax error\n", 13);
}