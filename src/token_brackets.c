#include "../include/minishell.h"

//TODO test :  echo ${USER} to check because it doesn't work
void	ft_get_expand_brackets_quotes(int *i, char *str, t_minishell *parse)
{
	char	*tmp;

	printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS_QUOTES --------------------\n" RESET);
	tmp = NULL;
	(*i)++;
	while (ft_isenvvarchar(str[++(*i)]))
	{
		tmp = ft_stock_char(tmp, str[(*i)]);
	}
	if (!tmp)
	{
		(*i)++;
		return ;
	}
	else
	{
		tmp = ft_stock_char(tmp, '=');
		tmp = ft_find_envvar(tmp, parse);
		if (tmp)
			ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	}
	ft_freenull(tmp);
	if (str[(*i)] != '}')
		return ; // put error message here
	else
		(*i)++;
	printf("char get expand = %c\n", str[(*i)]);
	parse->type = ARG;
	parse->flag_whitespace = 0;
}

void	ft_get_expand_brackets(int *i, t_minishell *parse)
{
	char	*tmp;

	printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS --------------------\n" RESET);
	tmp = NULL;
	(*i)++;
	printf("char get expand = %c\n", parse->input[(*i)]);
	while (ft_isenvvarchar(parse->input[++(*i)]))
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
	if (!tmp)
	{
		(*i)++;
		return ;
	}
	else
	{
		tmp = ft_stock_char(tmp, '=');
		tmp = ft_find_envvar(tmp, parse);
		if (tmp)
			ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	}
	ft_freenull(tmp);
	if (parse->input[(*i)] != '}')
		return ; // put error message here
	else
		(*i)++;
	parse->type = ARG;
	parse->flag_whitespace = 0;
}

bool	ft_check_expand_brackets(char *str, t_minishell *parse)
{
	int	i;

	printf(KYEL "-------------------- FT_CHECK_EXPAND_BRACKETS --------------------\n" RESET);
	i = 0;
	parse->c_brackets = OPEN;
	while (str[++i])
	{
		if(str[i] == '}')
		{
			parse->c_brackets = CLOSE;
			break;
		}
	}
	if (parse->c_brackets == CLOSE)
		return (true);
	return (false);
}

/* void	ft_brackets_token(int *i, t_minishell *parse)
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
} */

/* char	*ft_envvar_brackets_token(int *i, t_minishell *parse, char *str)
{
	//int		flag;
	char	*tmp;
	int		j;
	int		k;
	size_t	len;

	tmp = NULL;
	//flag = 0;
	printf(KYEL "---------- FT_ENVVAR_BRACKETS_TOKEN ----------\n" RESET);
	while (parse->input[++(*i)])
	{
		printf("char = %c\n", parse->input[(*i)]);
		if (parse->input[(*i)] == '{')
			(*i)++;
		if ((parse->input[(*i)] != '{') && (parse->input[(*i)] != '}') && (parse->input[(*i)] != 34))
		//if (ft_ismetac(parse->input[(*i)]) == 0)
			tmp = ft_stock_char(tmp, parse->input[(*i)]);
		//printf("tmp = %s\n", tmp);
		if (parse->input[(*i)] == '}' && flag)
			break ;
		if (parse->input[(*i)] == '}')
			break ;
		//if (parse->input[(*i) + 1] == 34 || parse->input[(*i)] == '}')
		if (ft_ismetachar(parse->input[(*i) + 1]) == 1)
		{
			(*i)++;
			break ;
		}
	}
	printf("char fin = %c\n", parse->input[(*i)]);
	tmp = ft_stock_char(tmp, '=');
	printf("tmp2 = %s\n", tmp);
	j = 0;
	len = ft_strlen(tmp);
	while (parse->envp[j] && ft_strncmp(parse->envp[j], tmp, len) != 0)
		j++;
	if (!parse->envp[j])
	{
		if (!str)
			write(1, "\n", 1);
		return (NULL);
	}
	tmp = NULL;
	k = len - 1;
	while (parse->envp[j][k++])
		tmp = ft_stock_char(tmp, parse->envp[j][k]);
	printf("tmp3 = %s\n", tmp);
	return (tmp);
} */
