#include "../include/minishell.h"

t_minishell	*ft_init_pars(void)
{
	static t_minishell	*pars;

	if (!pars)
	{
		pars = ft_calloc(1, sizeof(t_minishell));
		pars->line = NULL;
	}
	return (pars);
}
