#include "../include/minishell.h"
//TODO : gérer les parenthèses et les curly brackets

void	ft_reset_node(t_pars *pars)
{
	pars->type = ARG;
	pars->flag_whitespace = 0;
	pars->d_quotes = 0;
	pars->s_quotes = 0;
}

/* All char that aren't meta char (whitespace and isprint)*/
void	ft_char(char c, int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHAR --------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	(void)c;
	while (ft_iswhitespace(pars->input[(*i)]) == 1)
	{
		//printf("-> white space\n");
		pars->flag_whitespace = 1;
		(*i)++;
	}
	while (pars->input[(*i)] && ft_ismetachar(pars->input[(*i)]) == 0 \
		&& ft_iswhitespace(pars->input[(*i)]) == 0)
	{
		//printf("-> char = %c\n", pars->input[(*i)]);
		tmp = ft_stock_char(tmp, pars->input[(*i)]);
		(*i)++;
	}
	if (tmp)
	{
		ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
		tmp = NULL;
		ft_reset_node(pars);
	}
	//printf("-> i = %d\n", (*i));
	//printf("-> char fin = %c\n", parse->input[(*i)]);
}

/* Special char = whitespaces, pipe, < >, $ */
void	ft_metachar(char c, int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_METACHAR --------------------\n" RESET);
	//printf("-> char = %c\n", parse->input[(*i)]);
	//printf("-> i = %d\n", (*i));
	if (c == '|')
		ft_pipe_token(i, pars);
	else if (c == '<' && pars->input[(*i) + 1] == '<')
		ft_appenred_token(i, pars);
	else if (c == '<')
		ft_redin_token(i, pars);
	else if (c == '>' && pars->input[(*i) + 1] == '>')
		ft_heredoc_token(i, pars);
	else if (c == '>')
		ft_redout_token(i, pars);
	else if (c == '$')
		ft_envvar(i, pars);
	else if (c == '\"')
		ft_d_quotes_token(i, pars);
	else if (c == '\'')
		ft_s_quotes_token(i, pars);
}

bool	ft_ismetachar(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"' || c == '$')
		return (true);
	return (false);
}

void	ft_lexer(t_pars *pars)
{
	printf(KYEL "-------------------- FT_LEXER" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	int	i;

	i = 0;
	pars->strlen = ft_strlen(pars->input);
	printf("-> len = %zu\n", pars->strlen);
	while (i < (int)pars->strlen)
	{
		printf("-> char = %c\n", pars->input[(i)]);
		if (ft_ismetachar(pars->input[i]) == true)
			ft_metachar(pars->input[i], &i, pars);
		else
			ft_char(pars->input[i], &i, pars);
	}
	printf(KYEL "-------------------- FT_LEXER" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}
