#include "../include/minishell.h"

#define GWEN 0
#define LOULOU 0
#define LOULOU_JCT 1

int		g_exit_status;

void	ft_free_all(t_jct *jct, t_pars *pars, t_exec *exec)
{
	if (jct)
		ft_free_jct(jct);
	if (pars)
		ft_free_pars(pars);
	if (exec)
		ft_free_exec(exec);
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
	//TODO do we still need those 3 variables ?
	jct->file_in = 0;
	jct->file_out = 0;
	jct->fl_redirout = 0;
	return (jct);
}

/*
Main
prints a welcome message on the terminal
Infinite loop to wait for user input
*/
int	main(int ac, char **av, char **envp)
{
	(void)av;
	t_pars	*pars;
	t_exec	*exec;
	t_jct	*jct;

	// printf("\n😈😈😈 Welcome to minishell ... or should I say " RED"🔥 MINIHELLLL 🔥 😈😈😈\n\n"WHT);
	if (ac != 1)
	{
		ft_error(ERR_EXEC);
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, NULL);
	signal(SIGINT, &sig_handler);
	g_exit_status = 0;
	while (LOULOU_JCT)
	{
		jct = ft_init_jct(envp);
		pars = ft_init_pars(jct);
		pars->input = readline("Minishell > ");
		printf("pars->input = %s\n", pars->input);
		if (!pars->input)
		{
			printf("exit");
			break ;
		}
		add_history(pars->input);
		ft_parsing(pars);
		if (pars->jct->err_pars == false)
		{
			exec = ft_init_exec(jct);
			ft_exec(exec);
			ft_free_exec(exec);
		}
		ft_free_all(jct, pars, 0);
	}
	//TODO need to implement a fct that clears the history (fct clear_history exist in history.h)
	//TODO implement or add all free/reset function
	clear_history();
	ft_free_all(jct, pars, 0);
	return (g_exit_status);
}
