#include "../include/minishell.h"

void	ft_clean_up(t_pars *pars)
{
	if (pars)
	{
		if (pars->input)
			free(pars->input);
		free(pars);
	}
	exit(EXIT_SUCCESS);
}
