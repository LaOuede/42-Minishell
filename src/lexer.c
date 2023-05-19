#include "../include/minishell.h"
//TODO : gérer les parenthèses et les curly brackets

/* All char that aren't meta char (whitespace and isprint)*/
void	ft_char(char c, int *i, t_minishell *parse)
{
	char	*tmp;

	tmp = NULL;
	(void)c;
	printf(KYEL "---------- FT_CHAR ----------\n" RESET);
	while (ft_iswhitespace(parse->input[(*i)]) == 1)
	{
		printf("-> white space\n");
		parse->fl_ws = 1;
		(*i)++;
	}
	while (parse->input[(*i)] && ft_ismetachar(parse->input[(*i)]) == 0 \
		&& ft_iswhitespace(parse->input[(*i)]) == 0)
	{
		printf("-> char = %c\n", parse->input[(*i)]);
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
		(*i)++;
	}
	if (tmp)
	{
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
		tmp = NULL;
	}
	printf("-> i = %d\n", (*i));
	printf("-> char fin = %c\n", parse->input[(*i)]);
}

// TODO need to handle curly_brackets and parenthesis_brackets!!
/* Special char = whitespaces, pipe, < >, $ */
void	ft_metachar(char c, int *i, t_minishell *parse)
{
	printf(KYEL "---------- FT_METACHAR ----------\n" RESET);
	printf("-> char = %c\n", parse->input[(*i)]);
	printf("-> i = %d\n", (*i));
	if (c == '|')
		ft_pipe_token(i, parse);
	else if (c == '<' && parse->input[(*i) + 1] == '<')
		ft_appenred_token(i, parse);
	else if (c == '<')
		ft_redin_token(i, parse);
	else if (c == '>' && parse->input[(*i) + 1] == '>')
		ft_heredoc_token(i, parse);
	else if (c == '>')
		ft_redout_token(i, parse);
	else if (c == '(' || c == ')' || c == '{' || c == '}')
		ft_brackets_token(i, parse);
	else if (c == '$')
		ft_envvar_token(i, parse);
	else if (c == 34)
		ft_d_quotes_token(i, parse);
	else if (c == 39)
		ft_s_quotes_token(i, parse);
}

int	ft_ismetachar(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == 34 || c == 39
		|| c == '$' || c == '(' || c == '{')
		return (1);
	return (0);
}

void	ft_lexer(t_minishell *parse)
{
	int	i;

	i = 0;
	printf(KYEL "---------- FT_LEXER ---------- \n" RESET);
	parse->strlen = ft_strlen(parse->input);
	printf("-> len = %zu\n", parse->strlen);
	while (i < (int)parse->strlen)
	{
		printf("-> char = %c\n", parse->input[(i)]);
		if (ft_ismetachar(parse->input[i]) == 1)
			ft_metachar(parse->input[i], &i, parse);
		else
			ft_char(parse->input[i], &i, parse);
		printf("-> i = %d\n", i);
	}
}
