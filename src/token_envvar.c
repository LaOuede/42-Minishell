#include "../include/minishell.h"

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

bool	ft_isenvvarchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

void	ft_envvar_token(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_ENVVAR_TOKEN" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	while (ft_isenvvarchar(pars->input[++(*i)]))
		tmp = ft_stock_char(tmp, pars->input[(*i)]);
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

void	ft_envvar(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_ENVVAR" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	if (pars->input[(*i)] == '$' && pars->input[(*i) + 1] == '{')
	{
		if (ft_check_expand_brackets(pars->input, pars) == true)
			ft_get_expand_brackets(i, pars);
		else
			(*i)++;
	}
	else
		ft_envvar_token(i, pars);
	ft_reset_node(pars);
	printf(KYEL "-------------------- FT_ENVVAR" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}
