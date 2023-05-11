#include "../include/minishell.h"

void	ft_clean_up(t_minishell *parse)
{
	if (parse)
	{
		if (parse->input)
			free(parse->input);
		free(parse);
	}
	exit(EXIT_SUCCESS);
}
