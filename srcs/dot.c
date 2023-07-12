#include "minishell.h"

void	ft_dot(void)
{
	write(STDERR_FILENO, "minishell: .: filename argument required\n", 41);
}