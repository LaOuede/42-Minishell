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
		pars->flag_whitespace = 0;
	}
	//printf("-> i = %d\n", (*i));
	//printf("-> char fin = %c\n", parse->input[(*i)]);
}

/* TODO
1) DONE - No need to handle curly_brackets and parenthesis_brackets you fool!! 
So need to suppress functions
2) DONE - Also need to deal better with $ expansion.
https://www.gnu.org/software/bash/manual/html_node/Shell-Expansions.html 
watch out for $ and $$...
DONE - Need to deal with ${}
3) OK - Check if whitespace flag is working. If not, handle it! ==> I think it's ok
4) DONE - Deal with double quotes and only after that deal with $ inside
not both at the same time, the function is too huge!
5) DONE - Cleaning up the code a little bit
6) Handle memory wise girl !!
7) Re-construct the arguments
8) Clean up the linked-list
9) Transfer linked-list into 2D table
10) Parse commands
11) Shoot error message when a parsing error is found

12) Check everything to make a list of what's missing.
Lexer almost done. Parser here I come!
*/

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
		// TODO add flag for $ which is not an expansion but a normal char!
		if (ft_ismetachar(pars->input[i]) == true)
			ft_metachar(pars->input[i], &i, pars);
		else
			ft_char(pars->input[i], &i, pars);
		//printf("-> i = %d\n", i);
	}
	printf(KYEL "-------------------- FT_LEXER" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}
