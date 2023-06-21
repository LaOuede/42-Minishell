
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
static void	sig_child_handler(int sig)
{
	if (sig == SIGQUIT)
	{
/* 		rl_replace_line("", 0);
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		rl_on_new_line(); */
				write(1, "Quit: 3\n", 8);
		rl_on_new_line();
	}
	else if (sig == SIGINT)
	{
		g_exit_status = 1;
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		rl_already_prompted = 1;
	}
}

void	init_sig_handlers(void)
{
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_sig_exec_handlers(void)
{
	signal(SIGINT, &sig_child_handler);
	signal(SIGQUIT, &sig_child_handler);
}
