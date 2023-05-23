#include "../include/minishell.h"

/* void	ft_d_quotes_token(int *i, t_minishell *parse)
{
	int		j;
	char	*tmp;
	char	*envvar;

	j = *i;
	tmp = NULL;
	envvar = NULL;
	parse->type = D_QUOTES;
	parse->d_quotes = OPEN;
	printf(KYEL "---------- FT_D_QUOTES_TOKEN ----------\n" RESET);
	while (parse->input[++j])
	{
		if (parse->input[(j)] == 34)
		{
			parse->d_quotes = CLOSE;
			break ;
		}
	}
	while ((*i) < j)
	{
		if (parse->input[(*i)] == '$')
		{
			if (ft_ismetachar(parse->input[(*i) + 1]) == 0 \
				|| parse->input[(*i) + 1] == '{')
			{
				envvar = ft_envvar_quotes_token(i, parse, tmp);
				if (tmp && envvar)
					tmp = ft_strjoin(tmp, envvar);
				else if (!tmp && envvar)
					tmp = envvar;
			printf("char apres ennvar= %c\n", parse->input[(*i)]);
			}
		}
		else if (parse->input[(*i)] != 34)
		{
			if (envvar)
				tmp = ft_strjoin_char(tmp, parse->input[*i]);
			else
				tmp = ft_stock_char(tmp, parse->input[*i]);
		}
		(*i)++;
	}
	if (parse->input[(*i)] == 34)
		(*i)++;
	if (tmp)
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	ft_freenull(tmp);
	parse->d_quotes = 0;
	parse->type = ARG;
	parse->flag_whitespace = 0;
} */

void	ft_d_quotes_token(int *i, t_minishell *parse)
{
	char	*tmp;

	tmp = NULL;
	parse->type = D_QUOTES;
	parse->d_quotes = OPEN;
	printf(KYEL "-------------------- FT_D_QUOTES_TOKEN --------------------\n" RESET);
	while (parse->input[++(*i)] != '\"')
	{
		tmp = ft_stock_char(tmp, parse->input[*i]);
		if (parse->input[(*i)] == '$')
			parse->type = EXPAND;
	}
	if (parse->input[(*i)] == '\"')
	{
		parse->d_quotes = CLOSE;
		(*i)++;
	}
	printf("tmp = %s\n", tmp);
	if (tmp)
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	ft_freenull(tmp);
	parse->d_quotes = 0;
	parse->type = ARG;
	parse->flag_whitespace = 0;
}

void	ft_s_quotes_token(int *i, t_minishell *parse)
{
	char	*tmp;

	tmp = NULL;
	parse->type = S_QUOTES;
	parse->s_quotes = OPEN;
	printf(KYEL "-------------------- FT_S_QUOTES_TOKEN --------------------\n" RESET);
	while (parse->input[++(*i)] != '\'')
		tmp = ft_stock_char(tmp, parse->input[*i]);
	if (parse->input[(*i)] == '\'')
	{
		parse->s_quotes = CLOSE;
		(*i)++;
	}
	if (tmp)
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	ft_freenull(tmp);
	parse->s_quotes = 0;
	parse->type = ARG;
	parse->flag_whitespace = 0;
}
