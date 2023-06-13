#include "../include/minishell.h"

#define GWEN 0
#define LOULOU 0
#define LOULOU_JCT 1

t_jct	*g_jct;

t_jct	*ft_init_jct(void)
{
	t_jct	*jct;

	jct = ft_calloc(1, sizeof(t_jct));
	jct->tab = NULL;
	jct->cmd_nb = -1;
	jct->file_in = 0;
	jct->file_out = 0;
	jct->exit_status = -1;
	jct->fl_redirout = 0;
	jct->fds_in = NULL;
	jct->fds_out = NULL;
	jct->err_pars = false;
	return (jct);
}

/*
** Main
** prints a welcome message on the terminal
** Infinite loop pour attendre le user input
*/
int	main(int ac, char **av, char **envp)
{
	(void)av;
	t_pars	*pars;
	t_exec	*exec;
	int		test_mem;

	// printf("\n😈😈😈 Welcome to minishell ... or should I say " RED"🔥 MINIHELLLL 🔥 😈😈😈\n\n"WHT);
	// (void)test_mem;
	test_mem = 1;
	if (ac != 1)
	{
		printf("Too many arguments\nUsage: ./minishell\n");
		return(1);
	}
	pars = ft_init_pars(envp);
	g_jct = ft_init_jct();
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
		if (!pars->input)
		{
			printf("exit");
			break ;
		}
		add_history(pars->input);
		ft_parsing(pars);
		if (g_jct->err_pars == false)
		{
			exec = ft_init_exec(envp, g_jct);
			ft_print_debug(exec);
			ft_exec(exec, g_jct);
			//TODO implement a reset function instead of free fct
			ft_free_3tab(g_jct);
			ft_free_exec(exec);
		}
		g_jct->err_pars = false;
		test_mem -= 1;
	}
	
	//TODO need to implement a fct that clears the history (fct clear_history exist in history.h)
	//TODO implement or add all free/reset function
	ft_free_pars(pars);
	ft_free_jct();
	return (0);
}
