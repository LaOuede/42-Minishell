#include "../include/minishell.h"

void	*ft_get_expansion(char *str, int *i, t_minishell *parse)
{
	char	*tmp;

	printf("-------------------- FT_GET_EXPANSION --------------------\n");
	tmp = NULL;
	printf("i = %d\n", (*i));
	while (ft_isenvvarchar(str[++(*i)]))
		tmp = ft_stock_char(tmp, str[(*i)]);
	if (!tmp && str[(*i)] == '$')
		tmp = ft_stock_char(tmp, '$');
	else
	{
		tmp = ft_stock_char(tmp, '=');
		tmp = ft_find_envvar(tmp, parse);
	}
	printf("tmp = %s\n", tmp);
	return (tmp);
}

char	*ft_get_before(char *str, int *i)
{
	int		j;
	int		len;
	char	*save;

	printf("-------------------- FT_GET_BEFORE --------------------\n");
	len = 0;
	printf("i = %d\n", (*i));
	while (str[(*i)] || str[(*i)] != '$')
	{
		printf("c = %c\n", str[(*i)]);
		if (str[(*i)] == '$' || str[(*i)] == '\0')
			break ;
		(*i)++;
		len++;
	}
	j = (*i) - 1;
	save = ft_calloc(len + 1, sizeof(char));
	if (!save)
		return (NULL);
	while (len--)
	{
		save[len] = str[(j)];
		j--;
	}
	printf("save = %s\n", save);
	return (save);
}

bool	ft_strchr_expansion(char *str)
{
	int	i;
	printf("-------------------- FT_CHECK_EXPANSION --------------------\n");

	printf("str = %s\n", str);
	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

char	*ft_quotes_expansion(char *str, t_minishell *parse)
{
	int		i;
	char	*before;
	char	*expansion;
	char	*res;

	printf(KYEL "-------------------- FT_QUOTES_EXPANSION --------------------\n" RESET);
	i = 0;
	before = NULL;
	expansion = NULL;
	res = ft_calloc(1, sizeof(char));
	while (str[i])
	{
		before = ft_get_before(str, &i);
		if (before)
			res = ft_strjoin_free(res, before);
		before = NULL;
		expansion = ft_get_expansion(str, &i, parse);
		if (expansion)
			res = ft_strjoin_free(res, expansion);
		expansion = NULL;
	}
	printf("before = %s\n", before);
	printf("expansion = %s\n", expansion);
	printf("res = %s\n", res);
	return (res);
}
