#include "../include/minishell.h"

#define GWEN 0
#define LOULOU 0


int main(void)
{
	t_minishell	*parse;

/* 	if (GWEN){
		printf("gwen");
	} */
	printf("\n😈😈😈 Welcome to minishell ... should I say " RED"MINIHELLLL 😈😈😈\n\n"WHT);
	parse = ft_init_parse();
	while (1)
	{
		parse->input = readline("Minishell > ");
		ft_parse(parse);
	}
	ft_clean_up(parse);
}

/*
** Simple main that prints a message (printf) on the terminal
** Infinite loop pour attendre le user input
*/
/* int main()
{
	t_minishell	*pars;

	printf("\n😈😈😈 Welcome to minishell ... should I say " RED"MINIHELLLL 😈😈😈\n\n"WHT);
	pars = ft_init_pars();
	while (1)
		pars->line = readline("Minishell > ");
	ft_clean_up(pars);
}
 */