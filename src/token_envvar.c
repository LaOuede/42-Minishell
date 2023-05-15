#include "../include/minishell.h"

void	ft_envvar_token(int *i, t_minishell *parse)
{
	char	*tmp;
	char	*tmp2;
	int		j;
	int		k;
	size_t	len;

	tmp = NULL;
	printf("test\n");
	while (parse->input[++(*i)])
	{
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
		printf("char = %c\n", parse->input[(*i)]);
		if (ft_ismetac(parse->input[(*i)]) == 1)
			break ;
	}
	printf("tmp = %s\n", tmp);
	j = 0;
	len = ft_strlen(tmp);
	while (parse->envp[j] && ft_strncmp(parse->envp[j], tmp, len) != 0)
		j++;
	tmp2 = NULL;
/* 	printf("j = %d\n", j);
	printf("%s", parse->envp[j]); */
	k = len;
	while (parse->envp[j][k++])
	{
		printf("%c", parse->envp[j][k]);
	}
	printf("\n");
}
