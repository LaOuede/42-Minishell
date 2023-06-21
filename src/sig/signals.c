
#include "../../include/minishell.h"

/*
Handle signal outside forks:
	ctrl-C = display a new prompt on a new line
	ctrl-D = exit shell.
Update exit_status
*/
void	sig_handler(int sig)
{
	(void)sig;
	g_exit_status = 1;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
Handle signal in exec:
	ctrl-C = display a new prompt on a new line
	ctrl-D = display a new prompt on a new line.
Update exit_status
*/
void	sig_child_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (sig == SIGINT)
	{
		g_exit_status = 1;
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
	}
}

void	ft_init_sig(int phase)
{
	if (phase == MAIN)
	{
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (phase == EXEC)
	{
		signal(SIGINT, &sig_child_handler);
		signal(SIGQUIT, &sig_child_handler);
	}
}
