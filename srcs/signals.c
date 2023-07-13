#include "minishell.h"

void	ft_signal_handler(int signal_nb)
{
	struct termios	sa;
	struct termios	saved;

	tcgetattr(STDIN_FILENO, &sa);
	saved = sa;
	sa.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &sa);
	if (signal_nb == SIGINT)
	{
		rl_replace_line("", STDIN_FILENO);
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_error = 1;
	}
	else if (signal_nb == SIGQUIT)
		return ;
}

void	ft_ctrl_remove(int mode)
{
	struct termios ta;

	tcgetattr(STDIN_FILENO, &ta);
	if (mode == 1)
		ta.c_lflag &= ~ECHOCTL;
	else
		ta.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &ta);
}

void	ft_doing_nothing(int signal_nb)
{
	if (signal_nb == SIGINT)
		return ;
	else if (signal_nb == SIGQUIT)
		return ;
}

void	ft_doing_nothing_but_quit(int signal_nb)
{
	if (signal_nb == SIGINT)
		return ;
	else if (signal_nb == SIGQUIT)
	{
		printf("Quit :3\n");
		return ;
	}
}

void	ft_heredoc_handler(int signal_num)
{
	if (signal_num == SIGINT)
	{
		rl_replace_line("", STDIN_FILENO);
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		g_error = 1;
		exit(1);
	}
	else if (signal_num == SIGQUIT)
		return ;
}
