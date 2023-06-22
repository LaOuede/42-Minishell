#include "../../include/minishell.h"

bool	ft_isenvvarchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

/*
Handle regular chars and whitespaces
1) If whitespace, then move on and raise the whitespace flag for the builder.
2) If regular char, then stock char to memory and at the end create a new node.
*/
void	ft_char(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHAR --------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	while (ft_iswhitespace(pars->input[(*i)]) == 1)
	{
		printf("-> white space\n");
		pars->flag_whitespace = 1;
		(*i)++;
	}
	while (pars->input[(*i)] && ft_ismetachar(pars->input[(*i)]) == 0 \
		&& ft_iswhitespace(pars->input[(*i)]) == 0)
	{
		printf("-> char = %c\n", pars->input[(*i)]);
		tmp = ft_stock_char(tmp, pars->input[(*i)]);
		(*i)++;
	}
	if (tmp)
	{
		ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
		ft_freenull(tmp);
		ft_reset_node(pars);
	}
	printf("-> i = %d\n", (*i));
	printf("-> char fin = %c\n", pars->input[(*i)]);
}

void	ft_metachar(char c, int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_METACHAR --------------------\n" RESET);
	if (c == '|' || c == '<' || c == '>')
		ft_token(i, pars);
	else if (c == '$')
		ft_envvar(i, pars->input, pars);
	else if (c == '\"')
		ft_d_quotes_token(i, pars);
	else if (c == '\'')
		ft_s_quotes_token(i, pars);
}

bool	ft_ismetachar(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '$' || c == '\"' || c == '\'')
		return (true);
	return (false);
}

/*
Parsing Part I
Parse the input char by char looking for :
1) metachar (|, <, >, $, ', ")
2) regular char and whitespaces
3) stock tokens in a linked-list
*/
void	ft_lexer(t_pars *pars)
{
	printf(KYEL "-------------------- FT_LEXER" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	int	i;

	i = 0;
	pars->strlen = ft_strlen(pars->input);
	while (i < (int)pars->strlen)
	{
		printf("-> i = %d\n", (i));
		printf("-> char = %c\n", pars->input[(i)]);
		if (ft_ismetachar(pars->input[i]) == true)
			ft_metachar(pars->input[i], &i, pars);
		else
			ft_char(&i, pars);
	}
	printf(KYEL "-------------------- FT_LEXER" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}
