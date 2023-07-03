#include "../../include/minishell.h"

/*
Check for REDIN or REDOUT token at the end of the linked-list.
*/
void	ft_check_access(t_ms *ms)
{
	t_token	*ptr;
	int		counter;

	counter = 0;
	ptr = ms->pars->line;
	while (ptr)
	{
		if (ptr->type == ACCESS_ERR)
			counter += 1;
		ptr = ptr->next;
	}
	if (counter == ms->pars->nb_pipe)
		ft_error_parsing(0, PARSER, 127, ms);
}
