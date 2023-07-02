#include "../../include/minishell.h"

void	ft_get_expand_brackets(int *i, char *str, t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS" KGRN KBLD" START " RT KYEL "--------------------\n" RT);
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
			ft_add_token_bottom(&ms->pars->line, ft_create_node(ms, tmp, ms->pars));
	}
	tmp = ft_freenull(tmp);
	if (str[(*i)] != '}')
		ft_error_parsing(ERR_TOKEN, LEXER, 2, ms);
	else
		(*i)++;
	ft_reset_node(ms->pars);
	if (DEBUG)
		printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS" KRED KBLD" END " RT KYEL "--------------------\n" RT);
}

/*
Handle {} case
1) Look for closing }.
2) Raise an error flag if brackets aren't closed.
3) Return true if brackets are closed
*/
bool	ft_check_expand_brackets(char *str, t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_EXPAND_BRACKETS" KGRN KBLD" START " RT KYEL "--------------------\n" RT);
	ms->pars->c_brackets = OPEN;
	while (*str++)
	{
		if (*str == '}')
		{
			ms->pars->c_brackets = CLOSE;
			break ;
		}
	}
	if (ms->pars->c_brackets != 2)
		ft_error_parsing(ERR_QUOTE, LEXER, 2, ms);
	if (DEBUG)
	{
		printf("pars->c_brackets = %d\n", ms->pars->c_brackets);
		printf(KYEL "-------------------- FT_CHECK_EXPAND_BRACKETS" KRED KBLD" END " RT KYEL "--------------------\n" RT);
	}
	if (ms->pars->c_brackets == CLOSE)
		return (true);
	return (false);
}

char	*ft_find_envvar(char *str, t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_FIND_ENVVAR" KGRN KBLD" START " RT KYEL "--------------------\n" RT);
	int		i;
	size_t	len;
	char	*tmp;

	i = 0;
	tmp = NULL;
	len = ft_strlen(str);
	while (ms->envp[i] && ft_strncmp(ms->envp[i], str, len) != 0)
		i++;
	if (ms->envp[i])
	{
		ms->jct->flag_var = true;
		len -= 1;
		while (ms->envp[i][len++])
			tmp = ft_stock_char(ms, tmp, ms->envp[i][len]);
		str = ft_freenull(str);
	}
	if (!ms->envp[i])
	{
		tmp = ft_stock_char(ms, tmp, 29);
		str = ft_freenull(str);
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_FIND_ENVVAR" KRED KBLD" END " RT KYEL "--------------------\n" RT);
	return (tmp);
}

/*
1) If it's only $ char return it as a regular char and not an expansion
2) Look for expansion
*/
void	ft_envvar_token(int *i, char *str, t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_ENVVAR_TOKEN" KGRN KBLD" START " RT KYEL "--------------------\n" RT);
	char	*tmp;

	tmp = NULL;
	if (str[(*i + 1)] == '\"' || str[(*i + 1)] == '\'')
	{
		(*i)++;
		tmp = ft_stock_char(ms, tmp, 29);
		ft_add_token_bottom(&ms->pars->line, ft_create_node(ms, tmp, ms->pars));
		tmp = ft_freenull(tmp);
		return ;
	}
	while (ft_isenvvarchar(str[++(*i)]))
		tmp = ft_stock_char(ms, tmp, str[(*i)]);
	if (!tmp)
	{
		tmp = ft_stock_char(ms, tmp, '$');
		ft_add_token_bottom(&ms->pars->line, ft_create_node(ms, tmp, ms->pars));
	}
	else
	{
		tmp = ft_stock_char(ms, tmp, '=');
		tmp = ft_find_envvar(tmp, ms);
		ft_add_token_bottom(&ms->pars->line, ft_create_node(ms, tmp, ms->pars));
	}
	tmp = ft_freenull(tmp);
	if (DEBUG)
		printf(KYEL "-------------------- FT_ENVVAR_TOKEN" KRED KBLD" END " RT KYEL "--------------------\n" RT);
}

/*
Handle $ token
1) Look for {} char (eg: ${USER})
2) Look for ? char in order to deal with status exit [echo $?]
*/
void	ft_envvar(int *i, char *str, t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_ENVVAR" KGRN KBLD" START " RT KYEL "--------------------\n" RT);
	char 	*tmp;
	t_token	*ptr;

	tmp = NULL;
	ptr = ms->pars->line;
	while (ptr)
		ptr = ptr->next;
	if (str[(*i)] == '$' && str[(*i) + 1] == '{')
	{
		if (ft_check_expand_brackets(str, ms) == true)
			ft_get_expand_brackets(i, str, ms);
		else
			(*i)++;
	}
	else if (str[(*i)] == '$' && str[(*i) + 1] == '?')
	{
		(*i) += 2;
		if (ms->ctrlbs == true)
		{
			ms->ctrlbs = false;
			ms->flexit = 131;
		}
		else if (ms->ctrlc == true)
		{
			ms->ctrlc = false;
			ms->flexit = 130;
		}
		tmp = ft_itoa(ms->flexit);
		ft_add_token_bottom(&ms->pars->line, ft_create_node(ms, tmp, ms->pars));
		tmp = ft_freenull(tmp);
	}
	else
		ft_envvar_token(i, str, ms);
	ft_reset_node(ms->pars);
	if (DEBUG)
		printf(KYEL "-------------------- FT_ENVVAR" KRED KBLD" END " RT KYEL "--------------------\n" RT);
}
