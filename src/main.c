#include "../include/minishell.h"

#define GWEN 0
#define LOULOU 0
#define LOULOU_JCT 1

/* t_ms	*ft_init_ms(int ac, char **av, char **envp)
{
	static t_ms	*ms;

	if (!ms)
	{
		ft_calloc(1, sizeof(t_ms));
		ms->parsing = ft_init_parse(envp);
		ms->exec = ft_init_exec(ac, av , envp);
	}
	return (ms);
} */


t_jct	*ft_init_jct()
{
	t_jct	*jct;

	jct = ft_calloc(1, sizeof(t_jct));
	jct->tab = NULL;
	// jct->pipe_nb = -1;
	jct->cmd_nb = -1;
	jct->err_pars = true;
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
	(void)ac;
	t_pars	*pars;
	t_exec 	*exec;
	t_jct	*jct;
	int		test_mem;

	// printf("\n😈😈😈 Welcome to minishell ... or should I say " RED"🔥 MINIHELLLL 🔥 😈😈😈\n\n"WHT);
	(void)test_mem;
	pars = ft_init_pars(envp);
	jct = ft_init_jct();
	while (GWEN)
	{
		pars->input = readline("Minishell > ");
		add_history(pars->input);
		ft_parsing(pars, jct);
	}
	while (LOULOU_JCT)
	{
		pars->input = readline("Minishell > ");
		add_history(pars->input);
		ft_parsing(pars, jct);
		if (jct->err_pars == true)
		{
			exec = ft_init_exec(ac, av, envp);
			exec->cmd_nb = jct->cmd_nb;
			exec->pipes_nb = exec->cmd_nb - 1;
			ft_print_debug(exec);
			//The execution of all cmds starts here
			ft_exec_jct(exec, jct);
			//TODO implement a reset function instead of free fct
			ft_free_3tab(jct);
			ft_free_exec(exec);
		}
		jct->err_pars = true;
	}
	// while (LOULOU)
	// {
	// 	exec = ft_init_exec(ac, av, envp);
	// 	exec->line = readline("Minishell > ");
	// 	add_history(exec->line);
	// 	exec->readline = ft_split(exec->line, '|');

	// 	// //Printing What's inside 'exec->readline' variable
	// 	// int j = -1;
	// 	// while(exec->readline[++j])
	// 	// 	printf("exec->readline[%d] : %s\n", j, exec->readline[j]);
	// 	// ft_is_operator(exec);
	// 	ft_cmd_nb(exec);
	// 	ft_print_debug(exec);
	// 	//The execution of all cmds starts here
	// 	ft_exec(exec);
	// 	ft_free_exec(exec);
	// }
	
	// ft_clean_up(parse);
	//TODO need to implement a fct that clears the history (fct clear_history exist in history.h)
	return (0);
}
