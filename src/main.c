#include "../include/minishell.h"

#define GWEN 0
#define LOULOU 0
#define LOULOU_JCT 1

int		g_exit_status;

void	ft_free_child(t_ms *ms)
{
	if (ms)
	{
		if (ms->pars)
			ft_free_pars(ms->pars);
		if (ms->exec)
			ft_free_exec(ms->exec);
		ft_freenull(ms);
	}
}

void	ft_free_all(t_ms *ms)
{
	if (ms)
	{
		if (ms->jct)
			ft_free_jct(ms->jct);
		if (ms->pars)
			ft_free_pars(ms->pars);
		if (ms->exec)
			ft_free_exec(ms->exec);
		ft_freenull(ms);
	}
}

void	ft_reset_jct(t_jct *jct)
{
	free(jct->fds_in);
	jct->fds_in = NULL;
	free(jct->fds_out);
	jct->fds_out = NULL;
	ft_free_3tab(jct);
	jct->tab = NULL;
	jct->fd_hd = 0;
	jct->cmd_nb = -1;
	jct->err_pars = false;
}

/*
Initialization of the junction structure.
This structure holds all important data needed both in parsing and execution.
*/
t_jct	*ft_init_jct(char **envp)
{
	t_jct	*jct;

	jct = ft_calloc(1, sizeof(t_jct));
	jct->envp = NULL;
	ft_copy_env(jct, envp);
	jct->fds_in = NULL;
	jct->fds_out = NULL;
	jct->tab = NULL;
	jct->fd_hd = 0;
	jct->cmd_nb = -1;
	jct->err_pars = false;
	return (jct);
}

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
	}
	return (ms);
}

/*
Main
prints a welcome message on the terminal
Infinite loop to wait for user input
*/
int	main(int ac, char **av, char **envp)
{
	(void)av;
	t_ms	*ms;

	// printf("\n😈😈😈 Welcome to minishell ... or should I say " RED"🔥 MINIHELLLL 🔥 😈😈😈\n\n"WHT);
	if (ac != 1)
	{
		ft_error(ERR_EXEC);
		exit(EXIT_FAILURE);
	}
	g_exit_status = 0;
	while (LOULOU_JCT)
	{
		ms = ft_init_ms(envp);
		ft_init_sig(MAIN);
		ms->pars->input = readline("Minishell > ");
		printf("pars->input = %s\n", ms->pars->input);
		if (!ms->pars->input)
		{
			printf("exit");
			clear_history();
			ft_free_all(ms);
			exit(g_exit_status);
		}
		add_history(ms->pars->input);
		ft_parsing(ms);
		if (ms->jct->err_pars == false)
			ft_exec(ms);
		ft_reset_jct(ms->jct);
		//ft_free_all(ms);
	}
	//TODO need to implement a fct that clears the history (fct clear_history exist in history.h)
	//TODO implement or add all free/reset function
/* 	clear_history();
	ft_free_all(jct, pars, 0); */
	ft_free_all(ms);
	return (0);
}
