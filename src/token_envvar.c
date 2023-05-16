#include "../include/minishell.h"

void	ft_envvar_token(int *i, t_minishell *parse)
{
	char	*tmp;
	int		j;
	int		k;
	size_t	len;

	tmp = NULL;
	while (parse->input[++(*i)])
	{
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
		if (ft_ismetac(parse->input[(*i)]) == 1)
			break ;
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
}

char	*ft_envvar_quotes_token(int *i, t_minishell *parse, char *str)
{
	char	*tmp;
	int		j;
	int		k;
	size_t	len;

	tmp = NULL;
	while (parse->input[++(*i)] && ft_ismetac(parse->input[(*i)]) == 0)
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
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
	return (tmp);
}
