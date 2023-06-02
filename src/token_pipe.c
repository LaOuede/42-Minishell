#include "../include/minishell.h"

void	ft_pipe_token(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_PIPE_TOKEN --------------------\n" RESET);
	char	*tmp;
	int		j;

	j = (*i) + 1;
	while (pars->input[j])
	{
		if (pars->input[j] == '|')
		{
			ft_error("DOUBLE PIPE ERROR\n");
			pars->flag_error_lexer = true;
		}
		if (ft_iswhitespace(pars->input[j]) == 1)
			j++;
		else
			break ;
	}
	tmp = NULL;
	tmp = ft_stock_char(tmp, pars->input[(*i)]);
	pars->type = PIPE;
	pars->nb_pipe += 1;
	ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	(*i)++;
	ft_reset_node(pars);
}
