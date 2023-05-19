#include "../include/minishell.h"

void	ft_d_quotes_token(int *i, t_minishell *parse)
{
	int		j;
	int		flag;
	char	*tmp;
	char	*envvar;

	j = *i;
	printf("j start = %d\n", j);
	printf("i start = %d\n", (*i));
	flag = 0;
	tmp = NULL;
	envvar = NULL;
	parse->d_quotes = OPEN;
	printf("TEST QUOTE DOUBLE\n");
	printf("input = %s\n", parse->input);
/* 	while (parse->input[++j])
	{
		printf("char = %c\n", parse->input[j]);
		if (parse->input[((*i))] == 34)
		{
			parse->type = D_QUOTES;
			parse->d_quotes = CLOSE;
			break ;
		}
	} */
	while (parse->input[++j])
	{
		if (parse->input[(j)] == 34)
		{
			parse->type = D_QUOTES;
			parse->s_quotes = CLOSE;
			printf("parse->s_quotes = %d\n", parse->s_quotes);
			break ;
		}
	}
	printf("j = %d\n", j);
	printf("parse->type = %d\n", parse->type);
	if (parse->type == D_QUOTES)
	{
		printf("TEST QUOTE DOUBLE SUITE\n");
		while ((*i)++ < j)
		//while (parse->input[++(*i)] != 34)
		{
			if (parse->input[(*i)] == '$')
			{
				if (ft_ismetachar(parse->input[(*i) + 1]) == 0 || parse->input[(*i) + 1] == '{')
				{
					envvar = ft_envvar_quotes_token(i, parse, tmp);
					if (tmp && envvar)
						tmp = ft_strjoin(tmp, envvar);
					else if (!tmp && envvar)
						tmp = envvar;
					flag = 42;
					printf("tmp = %s\n", tmp);
				}
			}
			if (parse->input[(*i)] != 34)
			{
				if (flag)
					tmp = ft_strjoin_char(tmp, parse->input[*i]);
				else
					tmp = ft_stock_char(tmp, parse->input[*i]);
			}
		}
		if (tmp)
			ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
		parse->s_quotes = 0;
	}
	//++(*i);
	printf("char fin D_QUOTES = %c\n", parse->input[(*i)]);
	parse->type = ARG;
}

void	ft_s_quotes_token(int *i, t_minishell *parse)
{
	int		j;
	char	*tmp;
	int		gate;

	j = *i;
	tmp = NULL;
	gate = 0;
	parse->s_quotes = OPEN;
	printf("TEST QUOTE SIMPLE S\n");
	while (parse->input[++j])
	{
		if (parse->input[(j)] == 39)
		{
			parse->type = S_QUOTES;
			parse->s_quotes = CLOSE;
			printf("parse->s_quotes = %d\n", parse->s_quotes);
			break ;
		}
	}
	if (parse->type == S_QUOTES)
	{
		printf("coucou\n");
		while ((*i) < j)
		{
			printf("char = %c\n", parse->input[(*i)]);
			if (parse->input[(*i)] != 39)
				tmp = ft_stock_char(tmp, parse->input[*i]);
			(*i)++;
			gate = 42;
		}
		if (gate && tmp)
			ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
		parse->s_quotes = 0;
		printf("char = %c\n", parse->input[(j)]);
		++(*i);
		printf("TEST QUOTE SIMPLE Q\n");
	}
/* 	if (parse->type == S_QUOTES)
	{
		while (parse->input[++(*i)] != 39)
		{
			printf("char = %c\n", parse->input[(*i)]);
			tmp = ft_stock_char(tmp, parse->input[*i]);
			gate = 42;
		}
		printf("char fin = %c\n", parse->input[(*i)]);
		if (parse->input[(*i)] == 39 && gate)
		{
			++(*i);
			ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
			printf("char = %c\n", parse->input[(*i)]);
		}
		parse->s_quotes = 0;
	} */
	else
		++(*i);
	parse->type = ARG;
}
