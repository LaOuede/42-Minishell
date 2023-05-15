#include "../include/minishell.h"

#define GWEN 1
#define LOULOU 0

/*
** Main
** prints a welcome message on the terminal
** Infinite loop pour attendre le user input
*/
int	main(int ac, char **av, char **envp)
{
	t_minishell	*parse;
	t_exec 		*exec;
/* 	if (GWEN){
		printf("gwen");
	} */
	// printf("\n😈😈😈 Welcome to minishell ... or should I say " RED"🔥 MINIHELLLL 🔥 😈😈😈\n\n"WHT);
	parse = ft_init_parse(envp);
	while (GWEN)
	{
		parse->input = readline("Minishell > ");
		ft_parse(parse);
	}
	exec = ft_init_exec(ac, av , envp);
	while (LOULOU)
	{
		parse->input = readline("Minishell > ");
		ft_exec(exec);
	}
	
	// //Printing What's inside 'PATH' variable
	// int j = 0;
	// while(exec->cmd_paths[j])
	// 	printf("%s\n", exec->cmd_paths[j++]);
	
	ft_clean_up(parse);
}
