#include "../include/minishell.h"

#define GWEN 0
#define LOULOU 0

/*
** Main
** prints a welcome message on the terminal
** Infinite loop pour attendre le user input
*/
int	main(void)
{
	t_minishell	*parse;

/* 	if (GWEN){
		printf("gwen");
	} */
	printf("\n😈😈😈 Welcome to minishell ... or should I say " RED"🔥 MINIHELLLL 🔥 😈😈😈\n\n"WHT);
	parse = ft_init_parse();
	while (1)
	{
		parse->input = readline("Minishell > ");
		ft_parse(parse);
	}
	ft_clean_up(parse);
}
