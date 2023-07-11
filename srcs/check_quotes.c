#include "minishell.h"

static int	set_in_quotes(char c, int *in_quotes)
{
	int	cquotes;

	cquotes = *in_quotes;
	if (c == '\'')
	{
		if (cquotes == 0)
			*in_quotes = 1;
		else if (cquotes == 1)
			*in_quotes = 0;
	}
	if (c == '"')
	{
		if (cquotes == 0)
			*in_quotes = 2;
		else if (cquotes == 2)
			*in_quotes = 0;
	}
	return (cquotes);
}

void	ft_check_quotes(char *str)
{
	int	cur;
	int	in_quotes;

	cur = 0;
	in_quotes = 0;
	while (str[cur])
	{
		set_in_quotes(str[cur], &in_quotes);
		cur++;
	}
	if (in_quotes != 0)
		print_error(1, NULL);
	return ;
}