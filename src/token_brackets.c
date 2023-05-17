#include "../include/minishell.h"

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
	if (parse->input[(*i)] == '(')
	{
		parse->p_brackets = OPEN;
		while (parse->input[j++])
		{
			if (parse->input[(j)] == ')')
			{
				parse->p_brackets = CLOSE;
				break ;
			}
		}
		if (parse->p_brackets == CLOSE)
		{
			while (parse->input[(*i)++])
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
					printf("tmp = %s\n", tmp);
				}
				if (parse->input[(*i)] != ')')
				{
					if (flag)
						tmp = ft_strjoin_char(tmp, parse->input[*i]);
					else
						tmp = ft_stock_char(tmp, parse->input[*i]);
				}
				if (parse->input[(*i)] == ')')
				{
					(*i)++;
					break ;
				}
			}
			ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
			parse->p_brackets = 0;
		}
	}
	//TODO est-ce que c'Est nécessaire
/* 	if (parse->input[(*i)] == '{')
	{
		parse->c_brackets = OPEN;
		while (parse->input[j++])
		{
			if (parse->input[(j)] == '}')
			{
				parse->c_brackets = CLOSE;
				break ;
			}
		} */
		parse->c_brackets = OPEN;
		printf("parse->c_brackets = %d\n", parse->c_brackets);
		if (parse->c_brackets == OPEN)
		{
			if (parse->input[(*i)] == '$')
				{
					ft_envvar_token(i, parse);
				}
		}
		//else if (parse->c_brackets == CLOSE)
/* 		else
		{
			while (parse->input[(*i)])
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
				printf("char = %c\n", parse->input[(*i)]);
				if (parse->input[(*i)] != '}')
				{
					printf("test");
					if (flag)
						tmp = ft_strjoin_char(tmp, parse->input[*i]);
					else
						tmp = ft_stock_char(tmp, parse->input[*i]);
				}
				if (parse->input[(*i)] == '}')
					tmp = ft_stock_char(tmp, parse->input[*i]);
				(*i)++;
			}
			ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
			parse->c_brackets = 0;
		} */
/* 	}
	else
		return ; */
	parse->type = ARG;
}