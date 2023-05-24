#include "../include/minishell.h"
//TODO : gérer les parenthèses et les curly brackets

/* All char that aren't meta char (whitespace and isprint)*/
void	ft_char(char c, int *i, t_minishell *parse)
{
	char	*tmp;

	tmp = NULL;
	(void)c;
	printf(KYEL "-------------------- FT_CHAR --------------------\n" RESET);
	while (ft_iswhitespace(parse->input[(*i)]) == 1)
	{
		//printf("-> white space\n");
		parse->flag_whitespace = 1;
		(*i)++;
	}
	while (parse->input[(*i)] && ft_ismetachar(parse->input[(*i)]) == 0 \
		&& ft_iswhitespace(parse->input[(*i)]) == 0)
	{
		//printf("-> char = %c\n", parse->input[(*i)]);
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
		(*i)++;
	}
	if (tmp)
	{
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
		tmp = NULL;
		parse->flag_whitespace = 0;
	}
	//printf("-> i = %d\n", (*i));
	//printf("-> char fin = %c\n", parse->input[(*i)]);
}

/* TODO
1) No need to handle curly_brackets and parenthesis_brackets you fool!! 
So need to suppress functions - DONE
2) Also need to deal better with $ expansion.
https://www.gnu.org/software/bash/manual/html_node/Shell-Expansions.html 
watch out for $ and $$... - DONE /// Need to deal with ${}
3) Check is whitespace flag is working. If not, handle it! ==> I think it's ok
4) Deal with double quotes and only after that deal with $ inside
not both at the same time, the function is too huge! - DONE

5) Check everything to make a list of what's missing.
Lexer almost done. Parser here I come!
*/

/* Special char = whitespaces, pipe, < >, $ */
void	ft_metachar(char c, int *i, t_minishell *parse)
{
	printf(KYEL "-------------------- FT_METACHAR --------------------\n" RESET);
	//printf("-> char = %c\n", parse->input[(*i)]);
	//printf("-> i = %d\n", (*i));
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
	else if (c == '$')
		ft_envvar_token(i, parse);
	else if (c == '\"')
		ft_d_quotes_token(i, parse);
	else if (c == '\'')
		ft_s_quotes_token(i, parse);
}

bool	ft_ismetachar(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"' || c == '$')
		return (true);
	return (false);
}

void	ft_lexer(t_minishell *parse)
{
	int	i;

	i = 0;
	printf(KYEL "-------------------- FT_LEXER -------------------- \n" RESET);
	parse->strlen = ft_strlen(parse->input);
	//printf("-> len = %zu\n", parse->strlen);
	while (i < (int)parse->strlen)
	{
		printf("-> char = %c\n", parse->input[(i)]);
		// TODO add flag for $ which is not an expansion but a normal char!
		if (ft_ismetachar(parse->input[i]) == 1)
			ft_metachar(parse->input[i], &i, parse);
		else
			ft_char(parse->input[i], &i, parse);
		//printf("-> i = %d\n", i);
	}
}
