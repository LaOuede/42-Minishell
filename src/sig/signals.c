
#include "../../include/minishell.h"

/*
Handle signal outside forks:
	ctrl-C = display a new prompt on a new line
	ctrl-D = exit shell.
Update exit_status
*/
void	sig_handler(int sig)
{
	t_jct	*jct;

	jct = ft_init_jct();
	if (sig == SIGINT)
	{
		jct->exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
