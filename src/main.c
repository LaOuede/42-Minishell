#include "../include/minishell.h"

#define GWEN 0
#define LOULOU 1

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
	// t_ms		*ms;
	// t_minishell	*parse;
	t_exec 		*exec;
	
/* 	if (GWEN){
		printf("gwen");
	} */
	// printf("\n😈😈😈 Welcome to minishell ... or should I say " RED"🔥 MINIHELLLL 🔥 😈😈😈\n\n"WHT);
	// parse = ft_init_parse(envp);
	//ms = ft_init_ms(ac, av, envp);
	// while (GWEN)
	// {
	// 	parse->input = readline("Minishell > ");
	// 	ft_parse(parse);
	// }
	// printf("%p\n", exec);
	while (LOULOU)
	{
		int j;
		exec = ft_init_exec(ac, av, envp);
		exec->line = readline("Minishell > ");
		add_history(exec->line);
		exec->readline = ft_split(exec->line, '|');

		// /*
		// **	Printing What's inside 'exec->readline' variable
		// */
		// int j = -1;
		// while(exec->readline[++j])
		// 	printf("exec->readline[%d] : %s\n", j, exec->readline[j]);
		
		j = 0;
		while(exec->readline[j])
			j++;
		exec->cmd_nb = j;
		exec->pipes_nb = exec->cmd_nb - 1;
		// /*
		// **	Printing the cmd_nb
		// */
		// printf("cmd_nb = %d\n", j);
		// printf("pipes_nb = %d\n\n", exec->pipes_nb);

		/*
		**	The execution of all cmds starts here
		*/
		ft_exec(exec);
		ft_free_exec(exec);
	}
	
	// //Printing What's inside 'PATH' variable
	// int j = 0;
	// while(exec->cmd_paths[j])
	// 	printf("%s\n", exec->cmd_paths[j++]);
	
	// ft_clean_up(parse);
	return (0);
}
