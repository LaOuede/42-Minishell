#include "../include/minishell.h"

void	ft_clean_up(t_minishell *pars)
{
	if (pars)
	{
		if (pars->line)
			free(pars->line);
		free(pars);
	}
	exit(EXIT_SUCCESS);
}
