#include "../include/minishell.h"

bool	ft_check_expansion(char *str)
{
	int	i;
	printf(KYEL "-------------------- FT_CHECK_EXPANSION --------------------\n" RESET);

	printf("str = %s\n", str);
	i = -1;
	while (++str[i])
	{
		if (str[i] == '$')
			return (true);
	}
	return (false);
}

char	*ft_find_envvar(char* str, t_minishell *parse)
{
	int		i;
	int		j;
	size_t	len;
	char	*tmp;

	i = 0;
	len = ft_strlen(str);
	while (parse->envp[i] && ft_strncmp(parse->envp[i], str, len) != 0)
		i++;
	if (!parse->envp[i])
	{
		write(1, "\n", 1);
		return (NULL);
	}
	tmp = NULL;
	j = len - 1;
	while (parse->envp[i][j++])
		tmp = ft_stock_char(tmp, parse->envp[i][j]);
	return (tmp);
}

bool	ft_isenvvarchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

void	ft_envvar_token(int *i, t_minishell *parse)
{
	char	*tmp;

	printf(KYEL "-------------------- FT_ENVVAR --------------------\n" RESET);
	tmp = NULL;
	while (ft_isenvvarchar(parse->input[++(*i)]))
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
	if (!tmp)
	{
		tmp = ft_stock_char(tmp, '$');
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	}
	else
	{
		tmp = ft_stock_char(tmp, '=');
		tmp = ft_find_envvar(tmp, parse);
		if (tmp)
			ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	}
	ft_freenull(tmp);
}

char	*ft_strjoin_free(char *str1, char *str2)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	len;

	printf(KYEL "-------------------- FT_STRJOIN_FREE --------------------\n" RESET);
	if (!str1 || !str2)
		return (NULL);
	len = 0;
	while(*str2++)
		len++;
	len += ft_strlen(str1);
	printf("len = %zu\n", len);
	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);
	new_str = (char *)ft_calloc((len + 1), sizeof(char));
	i = 0;
	j = 0;
	while (str1[i])
		new_str[j++] = str1[i++];
	i = 0;
	while (str2[i])
		new_str[j++] = str2[i++];
	new_str[j] = '\0';
	ft_freenull(str1);
	return (new_str);
}

/* char	*ft_envvar_quotes_token(char *str, t_minishell *parse)
{
	int		i;
	char	*tmp;
	char	*new_str;

	printf(KYEL "-------------------- FT_ENVVAR_QUOTES_TOKEN --------------------\n" RESET);
	(void)parse;
	i = -1;
	tmp = NULL;
	new_str = (char *)ft_calloc(1, sizeof(char));
	while (str[++i])
	{
		if (str[i] != '$')
			tmp = ft_stock_char(tmp, str[i]);
		else if (str[i] == '$')
		{
			while (ft_isenvvarchar(str[++i]))
			{
				printf("test\n");
				tmp = ft_stock_char(tmp, str[i]);
			}
			tmp = ft_find_envvar(tmp, parse);
			printf("test tmp = %s\n", tmp);
		}
		if (tmp)
			new_str = ft_strjoin_free(new_str, tmp);
		printf("new_str = %s\n", new_str);
	}
	ft_freenull(str);
	return (new_str);
} */

/* void	ft_envvar_quotes_token(char *str, t_minishell *parse)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	printf(KYEL "-------------------- FT_ENVVAR_QUOTES_TOKEN --------------------\n" RESET);
	i = 0;
	tmp1 = NULL;
	tmp2 = NULL;
	printf("str = %s\n", str);
	while (str[i] != '$')
		tmp1 = ft_stock_char(tmp1, str[i++]);
	printf("tmp1 = %s\n", tmp1);
	if (tmp1)
		ft_add_token_bottom(&parse->line, ft_create_node(tmp1, parse));
		ft_add_token(&parse->line, ft_create_node(tmp1, parse));
	if (str[i] == '$')
		i++;
	while (ft_isenvvarchar(str[i]))
		tmp2 = ft_stock_char(tmp2, str[i++]);
	tmp2 = ft_stock_char(tmp2, '=');
	printf("tmp2 = %s\n", tmp2);
	tmp2 = ft_find_envvar(tmp2, parse);
	printf("tmp2 = %s\n", tmp2);
	if (tmp2)
		ft_add_token_bottom(&parse->line, ft_create_node(tmp2, parse));
		ft_add_token(&parse->line, ft_create_node(tmp2, parse));
	printf("str = %s\n", str);
	ft_freenull(tmp1);
	ft_freenull(tmp2);
} */

char	*ft_envvar_quotes_token(char *str, t_minishell *parse)
{
	(void)parse;
	int		i;
	char	*tmp1;
	char	*tmp2;
	char	*new_str;
	printf(KYEL "-------------------- FT_ENVVAR_QUOTES_TOKEN --------------------\n" RESET);

	i = -1;
	tmp1 = NULL;
	tmp2 = NULL;
	new_str = ft_calloc(1, sizeof(char));
	while (str[++i])
	{
		if (str[i] != '$')
			tmp1 = ft_stock_char(tmp1, str[i]);
		else
		{
			while (ft_isenvvarchar(str[++i]))
				tmp2 = ft_stock_char(tmp2, str[i]);
			tmp2 = ft_find_envvar(tmp2, parse);
		}
		if (tmp1 && tmp2)
			new_str = ft_strjoin_free(tmp1, tmp2);
	}
	return (new_str);
}

void	ft_expansion_quotes(t_minishell *parse)
{
	printf(KYEL "-------------------- FT_EXPANSION_QUOTES --------------------\n" RESET);
	t_token	*ptr;

	ptr = parse->line;
	while (ptr)
	{
		printf("TEST function\n");
		if (ptr->type == EXPAND)
		{
			printf(KRED "str expansion = %s\n" KRED, ptr->str);
			ptr->str = ft_envvar_quotes_token(ptr->str, parse);
			//printf(KMAG "res = %s\n" RESET, ptr->str);
			//ptr->type = ARG;
		}
		ptr = ptr->next;
	}
/* 	while (ptr)
		ptr = ptr->prev;
	while (ptr)
	{
		printf(KMAG "essai = %s\n" RESET, ptr->str);
		ptr = ptr->next;
	}
	parse->line = ft_find_head(&ptr);
	ft_free_lst(&ptr); */
}

/* void	ft_envvar_token(int *i, t_minishell *parse)
{
	char	*tmp;
	int		j;
	int		k;
	int		flag;
	size_t	len;

	tmp = NULL;
	flag = 0;
	printf(KYEL "-------------------- FT_ENVVAR --------------------\n" RESET);
	while (++(*i) < (int)parse->strlen)
	{
		printf("char = %c\n", parse->input[(*i)]);
		if (parse->input[(*i)] == '{')
		{
			flag = 42;
			(*i)++;
		}
		if (ft_ismetachar(parse->input[(*i)]) == 1 \
			|| ft_iswhitespace(parse->input[(*i)]) == 1 \
			|| (parse->input[(*i)] == '}' && !flag) \
			|| parse->input[(*i)] == '=')
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
} */

// TODO Need to handle when $ with nothing behind or $$
/* char	*ft_envvar_quotes_token(int *i, t_minishell *parse, char *str)
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
} */

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
