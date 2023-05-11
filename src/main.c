#include "../include/minishell.h"

int main(void)
{
	t_minishell	*pars;

	printf("\n😈😈😈 Welcome to minishell ... should I say " RED"MINIHELLLL 😈😈😈\n\n"WHT);
	pars = ft_init_pars();
	while (1)
	{
		pars->input = readline("Minishell > ");
		
	}
	ft_clean_up(pars);
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