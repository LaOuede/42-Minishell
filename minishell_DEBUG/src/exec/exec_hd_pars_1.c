#include "../../include/minishell.h"

void	ft_get_expand_brackets_hd(int *i, char *str, t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS_HD" KGRN KBLD" START " RT KYEL "--------------------\n" RT);
	char	*tmp;

	tmp = NULL;
	(*i)++;
	if (DEBUG)
		printf("char get expand = %c\n", str[(*i)]);
	while (ft_isenvvarchar(str[++(*i)]))
		tmp = ft_stock_char(ms, tmp, str[(*i)]);
	if (!tmp)
	{
		tmp = ft_stock_char(ms, tmp, '$');
		(*i)++;
	}
	else
	{
		tmp = ft_stock_char(ms, tmp, '=');
		tmp = ft_find_envvar(tmp, ms);
		if (tmp)
			ft_add_token_bottom(&ms->hd->line, ft_create_node(ms, tmp, ms->hd));
	}
	tmp = ft_freenull(tmp);
	if (str[(*i)] != '}')
		ms->hd->err_filler = true;
	else
		(*i)++;
	ft_reset_node(ms->hd);
	if (DEBUG)
		printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS_HD" KRED KBLD" END " RT KYEL "--------------------\n" RT);
}

bool	ft_check_expand_brackets_hd(char *str, t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_EXPAND_BRACKETS_HD" KGRN KBLD" START " RT KYEL "--------------------\n" RT);
	ms->hd->c_brackets = OPEN;
	while (*str++)
	{
		if (*str == '}')
		{
			ms->hd->c_brackets = CLOSE;
			break ;
		}
	}
	if (ms->hd->c_brackets != 2)
		ms->hd->err_parser = true;
	if (DEBUG){
	printf("hd->c_brackets = %d\n", ms->hd->c_brackets);
	printf(KYEL "-------------------- FT_CHECK_EXPAND_BRACKETS_HD" KRED KBLD" END " RT KYEL "--------------------\n" RT);
	}
	if (ms->hd->c_brackets == CLOSE)
		return (true);
	return (false);
}

void	ft_envvar_hd(int *i, char *str, t_ms *ms)
{
	if (DEBUG){
		printf(KYEL "-------------------- FT_ENVVAR_HD" KGRN KBLD" START " RT KYEL "--------------------\n" RT);
		printf("str[*i] = %c\n", str[*i]);
	}
	if (str[(*i)] == '$' && str[(*i) + 1] == '{')
	{
		if (ft_check_expand_brackets_hd(str, ms) == true)
			ft_get_expand_brackets_hd(i, str, ms);
		else
			(*i)++;
	}
	else if (str[(*i)] == '$' && str[(*i) + 1] == '?')
	{
		(*i) += 2;
		ft_add_token_bottom(&ms->hd->line, ft_create_node(ms, ft_itoa(ms->flexit), ms->hd));
	}
	else
		ft_envvar_token_hd(i, str, ms);
	ft_reset_node(ms->hd);
	if (DEBUG)
		printf(KYEL "-------------------- FT_ENVVAR_HD" KRED KBLD" END " RT KYEL "--------------------\n" RT);
}

void	ft_str_hd(int *i, t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_STR_HD --------------------\n" RT);
	char	*tmp;

	tmp = NULL;
	while ((ms->hd->input[(*i)]) && (ms->hd->input[(*i)] != '$'))
	{
		if (DEBUG)
			printf("-> char = %c\n", ms->hd->input[(*i)]);
		tmp = ft_stock_char(ms, tmp, ms->hd->input[(*i)]);
		(*i)++;
	}
	if (tmp)
	{
		ft_add_token_bottom(&ms->hd->line, ft_create_node(ms, tmp, ms->hd));
		tmp = ft_freenull(tmp);
		ft_reset_node(ms->hd);
	}
	if (DEBUG){
		printf("-> i = %d\n", (*i));
		printf("-> char fin = %c\n", ms->hd->input[(*i)]);
	}
}
