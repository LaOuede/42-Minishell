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
	parse->brackets = OPEN;
	while (parse->input[j++])
	{
		if (parse->input[(j)] == ')')
		{
			parse->brackets = CLOSED;
			break ;
		}
	}
	if (parse->brackets == CLOSED)
	{
		while (parse->input[(*i)++])
		{
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
		parse->brackets = 0;
	}
	else
		return ;
	parse->type = ARG;
}