#include "../include/minishell.h"

//TODO test :  echo ${USER} to check because it doesn't work
void	ft_brackets_token(int *i, t_minishell *parse)
{
	int		j;
	int		flag;
	char	*tmp;
	char	*envvar;

	j = *i;
	flag = 0;
	tmp = NULL;
	envvar = NULL;
	printf(KYEL "---------- FT_BRACKETS_TOKEN ----------\n" RESET);
	if (parse->input[(*i)] == '(')
	{
		parse->type = P_BRACKETS;
		parse->p_brackets = OPEN;
		printf(KYEL "---------- FT_P_BRACKETS_TOKEN ----------\n" RESET);
		while (parse->input[++j])
		{
			if (parse->input[(j)] == ')')
			{
				parse->p_brackets = CLOSE;
				break ;
			}
		}
		while ((*i) < j)
		{
			if (ft_iswhitespace(parse->input[(*i)]) == 1)
			{
				while (ft_iswhitespace(parse->input[(*i)]) == 1)
					(*i)++;
				tmp = ft_stock_char(tmp, ' ');
			}
			if (parse->input[(*i)] == '$')
			{
				envvar = ft_envvar_quotes_token(i, parse, tmp);
				if (tmp && envvar)
					tmp = ft_strjoin(tmp, envvar);
				else if (!tmp && envvar)
					tmp = envvar;
				flag = 42;
			}
			if (flag)
				tmp = ft_strjoin_char(tmp, parse->input[*i]);
			if (!flag)
				tmp = ft_stock_char(tmp, parse->input[*i]);
			(*i)++;
			if (parse->input[(*i)] == ')')
			{
				tmp = ft_stock_char(tmp, parse->input[*i]);
				break ;
			}
		}
		(*i)++;
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
		parse->p_brackets = 0;
	}
	else if (parse->input[(*i)] == '{')
	{
		parse->type = C_BRACKETS;
		parse->c_brackets = OPEN;
		printf(KYEL "---------- FT_C_BRACKETS_TOKEN ----------\n" RESET);
		while (parse->input[++j])
		{
			if (parse->input[(j)] == ')')
			{
				parse->c_brackets = CLOSE;
				break ;
			}
		}
		while ((*i) < j)
		{
			if (ft_iswhitespace(parse->input[(*i)]) == 1)
			{
				while (ft_iswhitespace(parse->input[(*i)]) == 1)
					(*i)++;
				tmp = ft_stock_char(tmp, ' ');
			}
			if (parse->input[(*i)] == '$')
			{
				envvar = ft_envvar_brackets_token(i, parse, tmp);
				if (tmp && envvar)
					tmp = ft_strjoin(tmp, envvar);
				else if (!tmp && envvar)
					tmp = envvar;
				flag = 42;
			}
			if (flag)
				tmp = ft_strjoin_char(tmp, parse->input[*i]);
			if (!flag)
				tmp = ft_stock_char(tmp, parse->input[*i]);
			(*i)++;
			if (parse->input[(*i)] == '}')
			{
				tmp = ft_stock_char(tmp, parse->input[*i]);
				break ;
			}
		}
		(*i)++;
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
		parse->c_brackets = 0;
	}
}
