#include "../include/minishell.h"

//TODO test :  echo ${USER} to check because it doesn't work
void	ft_get_expand_brackets_quotes(int *i, char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS_QUOTES" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*tmp;

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
		tmp = ft_find_envvar(tmp, pars);
		if (tmp)
			ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	}
	ft_freenull(tmp);
	if (str[(*i)] != '}')
		return ; // put error message here
	else
		(*i)++;
	printf("char get expand = %c\n", str[(*i)]);
	ft_reset_node(pars);
	printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS_QUOTES" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}

void	ft_get_expand_brackets(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	(*i)++;
	printf("char get expand = %c\n", pars->input[(*i)]);
	while (ft_isenvvarchar(pars->input[++(*i)]))
		tmp = ft_stock_char(tmp, pars->input[(*i)]);
	if (!tmp)
	{
		(*i)++;
		return ;
	}
	else
	{
		tmp = ft_stock_char(tmp, '=');
		tmp = ft_find_envvar(tmp, pars);
		if (tmp)
			ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	}
	ft_freenull(tmp);
	if (pars->input[(*i)] != '}')
		return ; // put error message here
	else
		(*i)++;
	ft_reset_node(pars);
	printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}

bool	ft_check_expand_brackets(char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_EXPAND_BRACKETS --------------------\n" RESET);
	pars->c_brackets = OPEN;
	while (*str++)
	{
		if (*str == '}')
		{
			pars->c_brackets = CLOSE;
			break ;
		}
	}
	if (pars->c_brackets == CLOSE)
		return (true);
	return (false);
}
