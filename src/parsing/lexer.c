#include "../../include/minishell.h"

/*
Handle regular chars and whitespaces
1) If whitespace, then move on and raise the whitespace flag for the builder.
2) If regular char, then stock char to memory and at the end create a new node.
*/
void	ft_char(int *i, t_ms *ms)
{
	char	*tmp;

	tmp = NULL;
	while (ft_iswhitespace(ms->pars->input[(*i)]) == 1)
	{
		ms->pars->fl_ws = 1;
		(*i)++;
	}
	while (ms->pars->input[(*i)] && ft_ismetachar(ms->pars->input[(*i)]) == 0 \
		&& ft_iswhitespace(ms->pars->input[(*i)]) == 0)
	{
		tmp = ft_stock_char(ms, tmp, ms->pars->input[(*i)]);
		(*i)++;
	}
	if (tmp)
	{
		ft_add_token_bottom(&ms->pars->line, ft_create_node(ms, tmp, ms->pars));
		tmp = ft_freenull(tmp);
		ft_reset_node(ms->pars);
	}
}

void	ft_metachar(char c, int *i, t_ms *ms)
{
	if (c == '|' || c == '<' || c == '>')
		ft_token(i, ms);
	else if (c == '$')
		ft_envvar(i, ms->pars->input, ms);
	else if (c == '\"')
		ft_d_quotes_token(i, ms);
	else if (c == '\'')
		ft_s_quotes_token(i, ms);
}

/*
Parsing Part I
Parse the input char by char looking for :
1) metachar (|, <, >, $, ', ")
2) regular char and whitespaces
3) stock tokens in a linked-list
*/
void	ft_lexer(t_ms *ms)
{
	int	i;

	i = 0;
	ms->pars->strlen = ft_strlen(ms->pars->input);
	while (i < (int)ms->pars->strlen)
	{
		if (ft_ismetachar(ms->pars->input[i]) == true)
			ft_metachar(ms->pars->input[i], &i, ms);
		else
			ft_char(&i, ms);
	}
}
