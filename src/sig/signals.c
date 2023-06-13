
#include "../../include/minishell.h"

/*
ctrl-C affiche un nouveau prompt sur une nouvelle ligne
ctrl-D quitte le shell.
ctrl-\ ne fait rien.
*/
void	signals_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		printf("exit\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGINT)
	{
		g_jct->exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
