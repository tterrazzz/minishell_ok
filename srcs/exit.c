#include "minishell.h"

/*	static void ft_error_exit calls the correct error message and sends it
	to the STDERR_FILENO */
static void	ft_error_exit(char *arg, int error)
{
	char	*str;
	char	*stock;

	if (!arg)
		return ;
	stock = NULL;
	if (error == NUMERIC)
	{
		stock = ft_strjoin("minishell: exit: ", arg);
		str = ft_strjoin(stock, ": numeric argument required\n");
		ft_free_ptr((void *) stock);
	}
	else
		str = ft_strdup("minishell: exit: too many arguments\n");
	write(STDERR_FILENO, str, ft_strlen(str));
	ft_free_ptr((void *) str);
}

/*	static int ft_check_long_max_min_get_nb will return an error if
	nb > LONG_MAX && nb < LONG_MIN */
static int	ft_check_long_max_min_get_nb(t_parsed *parsed, char *s, int sign)
{
	long long	nb;
	int			int_nb;

	if (!parsed || !s)
		return (-2147483648);
	nb = 0;
	int_nb = 0;
	while (*s >= '0' && *s <= '9')
	{
		if ((sign == 1 && nb >= 922337203685477580 && *s >= '8')
			|| (sign == -1 && ft_strlen(s) == 1 && nb <= 922337203685477580
				&& *s == '9'))
			return (-2147483648);
		nb = nb * 10 + (*s - 48);
		s++;
	}
	if (*s && !ft_isdigit(*s))
		return (-2147483648);
	int_nb = (int) nb;
	return (int_nb * sign);
}

/*	static int ft_atoi_exit gets the verification of each char inside str
	and returns nb * sign if it is a correct number */
static int	ft_atoi_exit(t_parsed *parsed, const char *str)
{
	char	*s;
	int		sign;

	if (!str)
		return (-2147483648);
	if (str && ft_isalpha(*str))
		return (-2147483648);
	sign = 1;
	s = (char *) str;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -sign;
		s++;
	}
	if ((sign == 1 && ft_strlen(s) > 19) || (sign == -1 && ft_strlen(s) > 20))
		return (-2147483648);
	if (*s && !ft_isdigit(*s))
		return (-2147483648);
	return (ft_check_long_max_min_get_nb(parsed, s, sign));
}

/*	int ft_exit is called when ctrl+d is pressed or when exit is written in
	non-interactive mode */
int	ft_exit(t_struct *s, t_parsed *parsed)
{
	if (!s || !parsed)
		return (1);
	if (!(parsed->prev) && !(parsed->next))
	{
		if (parsed->command[1])
		{
			g_st.error = ft_atoi_exit(parsed, parsed->command[1]);
			if (g_st.error == -2147483648)
			{
				write(STDOUT_FILENO, "exit\n", 5);
				ft_error_exit(parsed->command[1], NUMERIC);
				exit(255);
			}
			else if (!parsed->command[2])
				g_st.error %= 256;
			if (parsed->command[1] && parsed->command[2])
			{
				g_st.error = 1;
				return (ft_error_exit("too many", ARGUMENTS), 0);
			}
		}
		write(STDOUT_FILENO, "exit\n", 5);
		exit(g_st.error);
	}
	return (0);
}
