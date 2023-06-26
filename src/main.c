#include "../include/minishell.h"

#define LOULOU_IS_MAGIC 1

t_ms	*ft_init_ms(char **envp)
{
	static t_ms	*ms;

	(void)envp;
	if (!ms)
	{
		ms = ft_calloc(1, sizeof(t_ms));
		ms->jct = ft_init_jct(envp);
		ms->exec = ft_init_exec(ms);
		ms->pars = ft_init_pars(ms);
		ms->hd = NULL;
		ms->flexit = 0;
	}
	return (ms);
}

void	ft_minishell(t_ms *ms)
{
	while (LOULOU_IS_MAGIC)
	{
		ft_init_sig(MAIN);
		ms->pars->input = readline("Miniꞩhell > ");
		if (!ms->pars->input)
		{
			printf("exit");
			ft_exit_free(ms, 0);
		}
		add_history(ms->pars->input);
		ft_parsing(ms);
		if (ms->jct->err_pars == false)
			ft_exec(ms);
		ft_reset_jct(ms->jct);
	}
	ft_exit_free(ms, 0);
}

/*
Main
prints a welcome message on the terminal
Infinite loop to wait for user input
*/
int	main(int ac, char **av, char **envp)
{
	t_ms	*ms;
	// printf("\n😈😈😈 Welcome to minishell ... or should I say " RED"🔥 MINIHELLLL 🔥 😈😈😈\n\n"WHT);
	(void)av;
	ms = ft_init_ms(envp);
	if (ac != 1)
	{
		ft_error(ERR_EXEC);
		exit(127);
	}
	ft_minishell(ms);
	return (0);
}
