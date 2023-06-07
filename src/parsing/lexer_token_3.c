#include "../../include/minishell.h"

void	*ft_get_expansion(char *str, int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_GET_EXPANSION" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	printf("i = %d\n", (*i));
	printf("char get expansion = %c\n", str[(*i)]);
	if (str[(*i)] == '$' && str[(*i) + 1] == '{')
	{
		if (ft_check_expand_brackets(str, pars) == true)
			tmp = ft_get_expand_brackets_quotes(i, str, pars);
	}
	else
	{
		while (ft_isenvvarchar(str[++(*i)]))
			tmp = ft_stock_char(tmp, str[(*i)]);
		if (!tmp && str[(*i)] == '$')
			tmp = ft_stock_char(tmp, '$');
		else
		{
			printf("tmp = %s\n", tmp);
			tmp = ft_stock_char(tmp, '=');
			tmp = ft_find_envvar(tmp, pars);
		}
	}
	printf("tmp = %s\n", tmp);
	printf(KYEL "-------------------- FT_GET_EXPANSION" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	return (tmp);
}

char	*ft_get_before(char *str, int *i)
{
	printf(KYEL "-------------------- FT_GET_BEFORE" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	int		j;
	int		len;
	char	*save;

	len = 0;
	save = NULL;
	while (str[(*i)] || str[(*i)] != '$')
	{
		printf("-> char = %c\n", str[(*i)]);
		if (str[(*i)] == '$' || str[(*i)] == '\0')
			break ;
		(*i)++;
		len++;
	}
	j = (*i) - 1;
	save = ft_calloc(len + 1, sizeof(char));
	while (len--)
	{
		save[len] = str[j];
		j--;
	}
	printf("-> save = %s\n", save);
	printf(KYEL "-------------------- FT_GET_BEFORE" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	return (save);
}

char	*ft_quotes_expansion(char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_QUOTES_EXPANSION" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	int		i;
	char	*save;
	char	*res;
	char	*tmp;

	i = 0;
	save = NULL;
	tmp = NULL;
	res = ft_calloc(1, sizeof(char));
	while (str[i] && pars->c_brackets != 1)
	{
		save = ft_get_before(str, &i);
		if (save)
			res = ft_strjoin_free(res, save);
		printf("-> before = %s\n", save);
		printf("-> res = %s\n", res);
		save = NULL;
		save = ft_get_expansion(str, &i, pars);
		printf("save = %s\n", save);
		if (save)
		{
			printf("test");
			res = ft_strjoin_free(res, save);
		}
		printf("-> expansion = %s\n", save);
		save = NULL;
	}
	printf("-> res = %s\n", res);
	printf(KYEL "-------------------- FT_QUOTES_EXPANSION" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	return (res);
}
