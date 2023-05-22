#include "../include/minishell.h"

#define GWEN 1
#define LOULOU 0

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

/*
** Main
** prints a welcome message on the terminal
** Infinite loop pour attendre le user input
*/
int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;
	// t_ms		*ms;
	t_minishell	*parse;
	t_exec 		*exec;

	// printf("\n😈😈😈 Welcome to minishell ... or should I say " RED"🔥 MINIHELLLL 🔥 😈😈😈\n\n"WHT);
	parse = ft_init_parse(envp);
	//ms = ft_init_ms(ac, av, envp);
	while (GWEN)
	{
		parse->input = readline("Minishell > ");
		add_history(parse->input);
		ft_parse(parse);
	}
	//printf("%p\n", exec);
	//exec = ft_init_exec(ac, av, envp);
	while (LOULOU)
	{
		exec = ft_init_exec(ac, av, envp);
		exec->line = readline("Minishell > ");
		add_history(exec->line);

		exec->readline = ft_split(exec->line, ' ');

		//TODO Write this command below
		ft_is_operator(exec);
		
		ft_cmd_nb(exec);
		ft_print_debug(exec);
		// if (ft_is_redirout(exec))
		// {
		// 	exec->outfile = ft_split(exec->readline[exec->fl_redirout_i], '>');
		// 	//Printing What's inside 'exec->outfile' variable
		// 	printf("---	Printing exec->outfile[i]	---\n");
		// 	int j = -1;
		// 	while(exec->outfile[++j])
		// 		printf("exec->outfile[%d] : %s\n", j, exec->outfile[j]);
		
		// }
	
		//The execution of all cmds starts here
		// ft_exec(exec);
		ft_free_exec(exec);
	}
	
	// //Printing What's inside 'PATH' variable
	// int j = 0;
	// while(exec->cmd_paths[j])
	// 	printf("%s\n", exec->cmd_paths[j++]);
	
	// ft_clean_up(parse);
	return (0);
}
