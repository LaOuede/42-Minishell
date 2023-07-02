#include "../../include/minishell.h"

/*
Handle signal outside forks:
	SIGINT / ctrl-C = display a new prompt on a new line
	SIGQUIT / ctrl-D = exit shell.
*/
void	sig_handler(int sig)
{
	t_ms	*ms;

	(void)sig;
	ms = ft_init_ms(0);
	ms->ctrlc = true;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
Handle signal in exec:
	SIGINT / ctrl-C = display a new prompt on a new line
	SIGQUIT / ctrl-\ = exit child.
*/
void	sig_child_handler(int sig)
{
	t_ms	*ms;

	ms = ft_init_ms(0);
	if (sig == SIGQUIT)
	{
		ms->ctrlbs = true;
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (sig == SIGINT)
	{
		ms->ctrlc = true;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

/*
Handle signal in Heredoc:
	SIGINT / ctrl-C = display a new prompt on a new line
*/
void	sig_hd_handler(int sig)
{
	t_ms	*ms;

	(void)sig;
	ms = ft_init_ms(0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_exit_free(ms, 1, 0);
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
	else if (phase == HD)
	{
		signal(SIGINT, &sig_hd_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
