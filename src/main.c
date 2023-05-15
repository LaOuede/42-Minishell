#include "../include/minishell.h"
// #include "../include/execution.h"

#define GWEN 0
#define LOULOU 1

t_ms	*ft_init_ms(int ac, char **av, char **envp)
{
	static t_ms	*ms;

	if (!ms)
	{
		ms->parsing = ft_init_parse();
		ms->exec = ft_init_exec(ac, av , envp);
	}
	return (ms);
}

/*
** Main
** prints a welcome message on the terminal
** Infinite loop pour attendre le user input
*/
int	main(int ac, char **av, char **envp)
{
	t_ms		*ms;
	// t_minishell	*parse;
	// t_exec 		*exec;
/* 	if (GWEN){
		printf("gwen");
	} */
	// printf("\n😈😈😈 Welcome to minishell ... or should I say " RED"🔥 MINIHELLLL 🔥 😈😈😈\n\n"WHT);
	parse = ft_init_parse(envp);
	while (GWEN)
	{
		ms->parsing->input = readline("Minishell > ");
		ft_parse(ms->parsing);
	}
	while (LOULOU)
	{
		ms->parsing->input = readline("Minishell > ");
		ft_exec(ms->exec);
	}
	
	// //Printing What's inside 'PATH' variable
	// int j = 0;
	// while(exec->cmd_paths[j])
	// 	printf("%s\n", exec->cmd_paths[j++]);
	
	ft_clean_up(ms->parsing);
}
