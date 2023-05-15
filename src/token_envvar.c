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
		printf("char = %c\n", parse->input[(*i)]);
		if (ft_ismetac(parse->input[(*i)]) == 1)
			break ;
	}
	tmp = ft_stock_char(tmp, '=');
	j = 0;
	len = ft_strlen(tmp);
	while (parse->envp[j] && ft_strncmp(parse->envp[j], tmp, len) != 0)
		j++;
	if (!parse->envp[j])
		return ;
	tmp = NULL;
	k = len - 1;
	while (parse->envp[j][k++])
		tmp = ft_stock_char(tmp, parse->envp[j][k]);
	ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	free(tmp);
}
