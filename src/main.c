#include "../include/minishell.h"

/* Parsing main*/
int	main()
{
	t_minishell	*pars;

	printf("\n😈😈😈 Welcome to minishell 😈😈😈\n\n");
	pars = ft_init_pars();
	while (1)
		pars->line = readline("Minishell > ");
	ft_clean_up(pars);
}
