#include "../../include/minishell.h"

void	ft_get_expand_brackets(int *i, char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	(*i)++;
	printf("char get expand = %c\n", str[(*i)]);
	while (ft_isenvvarchar(str[++(*i)]))
		tmp = ft_stock_char(tmp, str[(*i)]);
	if (!tmp)
	{
		tmp = ft_stock_char(tmp, '$');
		(*i)++;
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
		ft_error_parsing(ERR_TOKEN, LEXER, 2, pars);
	else
		(*i)++;
	ft_reset_node(pars);
	printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}

/*
Handle {} case
1) Look for closing }.
2) Raise an error flag if brackets aren't closed.
3) Return true if brackets are closed
*/
bool	ft_check_expand_brackets(char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_EXPAND_BRACKETS" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	pars->c_brackets = OPEN;
	while (*str++)
	{
		if (*str == '}')
		{
			pars->c_brackets = CLOSE;
			break ;
		}
	}
	if (pars->c_brackets != 2)
		ft_error_parsing(ERR_QUOTE, LEXER, 2, pars);
	printf("pars->c_brackets = %d\n", pars->c_brackets);
	printf(KYEL "-------------------- FT_CHECK_EXPAND_BRACKETS" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	if (pars->c_brackets == CLOSE)
		return (true);
	return (false);
}

char	*ft_find_envvar(char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_FIND_ENVVAR" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	int		i;
	size_t	len;
	char	*tmp;

	i = 0;
	len = ft_strlen(str);
	while (pars->envp[i] && ft_strncmp(pars->envp[i], str, len) != 0)
		i++;
	if (!pars->envp[i])
	{
		write(1, "\n", 1);
		return (NULL);
	}
	tmp = NULL;
	len -= 1;
	while (pars->envp[i][len++])
		tmp = ft_stock_char(tmp, pars->envp[i][len]);
	ft_freenull(str);
	printf(KYEL "-------------------- FT_FIND_ENVVAR" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	return (tmp);
}

/*
1) If it's only $ char return it as a regular char and not an expansion
2) Look for expansion
*/
void	ft_envvar_token(int *i, char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_ENVVAR_TOKEN" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	while (ft_isenvvarchar(str[++(*i)]))
		tmp = ft_stock_char(tmp, str[(*i)]);
	if (!tmp)
	{
		tmp = ft_stock_char(tmp, '$');
		ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	}
	else
	{
		tmp = ft_stock_char(tmp, '=');
		tmp = ft_find_envvar(tmp, pars);
		if (tmp)
			ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	}
	ft_freenull(tmp);
	printf(KYEL "-------------------- FT_ENVVAR_TOKEN" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}

/*
Handle $ token
1) Look for {} char (eg: ${USER})
2) Look for ? char in order to deal with status exit [echo $?]
*/
void	ft_envvar(int *i, char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_ENVVAR" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;

	ptr = pars->line;
	while (ptr->next)
		ptr = ptr->next;
	printf("ptr->str = %s\n", ptr->str);
	if (str[(*i)] == '$' && str[(*i) + 1] == '{')
	{
		if (ft_check_expand_brackets(str, pars) == true)
			ft_get_expand_brackets(i, str, pars);
		else
			(*i)++;
	}
	else if (str[(*i)] == '$' && str[(*i) + 1] == '?')
	{
		(*i) += 2;
		ft_add_token_bottom(&pars->line, ft_create_node(ft_itoa(g_exit_status), pars));
	}
	else
		ft_envvar_token(i, str, pars);
	ft_reset_node(pars);
	printf(KYEL "-------------------- FT_ENVVAR" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}
