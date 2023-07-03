#include "../../include/minishell.h"

bool	ft_ismetachar(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '$' || c == '\"' || c == '\'')
		return (true);
	return (false);
}

bool	ft_isenvvarchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

void	ft_exit_status(t_ms *ms, int *i)
{
	char	*tmp;

	tmp = NULL;
	(*i) += 2;
	if (ms->ctrlbs == true)
	{
		ms->ctrlbs = false;
		ms->flexit = 131;
	}
	else if (ms->ctrlc == true)
	{
		ms->ctrlc = false;
		ms->flexit = 130;
	}
	tmp = ft_itoa(ms->flexit);
	ft_add_token_bottom(&ms->pars->line, ft_create_node(ms, tmp, ms->pars));
	tmp = ft_freenull(tmp);
}
