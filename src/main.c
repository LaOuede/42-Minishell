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
	(void)ac;
	(void)av;
	// t_ms		*ms;
	t_minishell	*parse;
	t_exec 		*exec;
/* 	if (GWEN){
		printf("gwen");
	} */
	// printf("\n😈😈😈 Welcome to minishell ... or should I say " RED"🔥 MINIHELLLL 🔥 😈😈😈\n\n"WHT);
	parse = ft_init_parse(envp);
	//ms = ft_init_ms(ac, av, envp);
	while (GWEN)
	{
		parse->input = readline("Minishell > ");
		ft_parse(parse);
	}
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
