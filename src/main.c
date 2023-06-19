#include "../include/minishell.h"

#define GWEN 0
#define LOULOU 0
#define LOULOU_JCT 1

/*
Initialization of the junction structure.
This structure holds all important data needed both in parsing and execution.
*/
t_jct	*ft_init_jct(void)
{
	static t_jct	*jct;

	if (!jct)
	{
		jct = ft_calloc(1, sizeof(t_jct));
		jct->fds_in = NULL;
		jct->fds_out = NULL;
		jct->tab = NULL;
		jct->cmd_nb = -1;
		jct->err_pars = false;
		jct->exit_status = 0;
		//TODO do we still need those 3 variables ?
		jct->file_in = 0;
		jct->file_out = 0;
		jct->fl_redirout = 0;
	}
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
	//int		test_mem;

	// printf("\n😈😈😈 Welcome to minishell ... or should I say " RED"🔥 MINIHELLLL 🔥 😈😈😈\n\n"WHT);
	// (void)test_mem;
	//test_mem = 1;
	if (ac != 1)
	{
		printf("Too many arguments\nUsage: ./minishell\n");
		return(1);
	}
	jct = ft_init_jct();
	pars = ft_init_pars(envp);
	// while (GWEN)
	// {
	// 	pars->input = readline("Minishell > ");
	// 	add_history(pars->input);
	// 	ft_parsing(pars, jct);
	// }
	//while (test_mem != 0)
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, NULL);
	while (LOULOU_JCT)
	{
		pars->input = readline("Minishell > ");
		printf("pars->input = %s\n", pars->input);
		if (!pars->input)
		{
			printf("exit");
			break ;
		}
		add_history(pars->input);
		ft_parsing(pars);
		printf("jct->err_pars = %d\n", jct->err_pars);
		if (jct->err_pars == false)
		{
			exec = ft_init_exec(envp, jct);
			ft_exec(exec, jct);
			//TODO implement a reset function instead of free fct
			ft_free_3tab(jct);
			ft_free_exec(exec);
		}
		jct->err_pars = false;
		//test_mem -= 1;
	}
	
	//TODO need to implement a fct that clears the history (fct clear_history exist in history.h)
	//TODO implement or add all free/reset function
	ft_free_pars(pars);
	ft_free_jct(jct);
	return (0);
}
