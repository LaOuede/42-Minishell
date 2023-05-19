#include "../include/minishell.h"

void	ft_envvar_token(int *i, t_minishell *parse)
{
	char	*tmp;
	int		j;
	int		k;
	int		flag;
	size_t	len;

	tmp = NULL;
	flag = 0;
	printf(KYEL "---------- FT_ENVVAR ----------\n" RESET);
	while (++(*i) < (int)parse->strlen)
	{
		printf("char = %c\n", parse->input[(*i)]);
		if (parse->input[(*i)] == '{')
		{
			flag = 42;
			(*i)++;
		}
		if (ft_ismetachar(parse->input[(*i)]) == 1
			|| ft_iswhitespace(parse->input[(*i)]) == 1 || (parse->input[(*i)] == '}' && !flag))
			break ;
		if (parse->input[(*i)] == '}' && flag)
		{	
			(*i)++;
			break ;
		}
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
	}
	tmp = ft_stock_char(tmp, '=');
	j = 0;
	len = ft_strlen(tmp);
	while (parse->envp[j] && ft_strncmp(parse->envp[j], tmp, len) != 0)
		j++;
	if (!parse->envp[j])
	{
		write(1, "\n", 1);
		return ;
	}
	tmp = NULL;
	k = len - 1;
	while (parse->envp[j][k++])
		tmp = ft_stock_char(tmp, parse->envp[j][k]);
	ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	free(tmp);
	printf("char fin ENVVAR = %c\n", parse->input[(*i)]);
	return ;
}

/* void	ft_envvar_token(int *i, t_minishell *parse)
{
	char	*tmp;
	int		j;
	int		k;
	size_t	len;

	tmp = NULL;
	printf("TEST");
	while (parse->input[++(*i)])
	{
		if (parse->input[(*i)] == '{')
			(*i)++;
		if (parse->input[(*i)] != '}')
			tmp = ft_stock_char(tmp, parse->input[(*i)]);
		if (parse->input[(*i)] == '}' && parse->c_brackets == OPEN)
			break ;
	}
	printf("tmp = %s\n", tmp);
	tmp = ft_stock_char(tmp, '=');
	j = 0;
	len = ft_strlen(tmp);
	while (parse->envp[j] && ft_strncmp(parse->envp[j], tmp, len) != 0)
		j++;
	if (!parse->envp[j])
	{
		write(1, "\n", 1);
		return ;
	}
	tmp = NULL;
	k = len - 1;
	while (parse->envp[j][k++])
		tmp = ft_stock_char(tmp, parse->envp[j][k]);
	printf("!!! parse->c_brackets = %d\n", parse->c_brackets);
	printf("char = %c\n", parse->input[(*i)]);
	if (parse->c_brackets == OPEN)
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
	ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	free(tmp);
} */


// TODO Need to handle when $ with nothing behind or $$
char	*ft_envvar_quotes_token(int *i, t_minishell *parse, char *str)
{
	int		flag;
	char	*tmp;
	int		j;
	int		k;
	size_t	len;

	tmp = NULL;
	flag = 0;
	printf(KYEL "---------- FT_ENVVAR_QUOTES_TOKEN ----------\n" RESET);
	while (++(*i) < (int)parse->strlen)
	{
		printf("char = %c\n", parse->input[(*i)]);
		if (parse->input[(*i)] == '{')
		{
			flag = 42;
			(*i)++;
		}
		if (ft_ismetachar(parse->input[(*i)]) == 1 \
			|| ft_iswhitespace(parse->input[(*i)]) == 1 || (parse->input[(*i)] == '}' && !flag))
		{
			(*i)--;
			break ;
		}
		if (parse->input[(*i)] == '}' && flag)
		{	
			(*i)++;
			break ;
		}
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
	}
	tmp = ft_stock_char(tmp, '=');
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
	printf("char fin = %c\n", parse->input[(*i)]);
	return (tmp);
}

char	*ft_envvar_brackets_token(int *i, t_minishell *parse, char *str)
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
/* 		if (parse->input[(*i)] == '}' && flag)
			break ; */
/* 		if (parse->input[(*i)] == '}')
			break ; */
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
}
