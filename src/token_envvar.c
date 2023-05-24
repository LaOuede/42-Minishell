#include "../include/minishell.h"

char	*ft_find_envvar(char *str, t_minishell *parse)
{
	int		i;
	int		j;
	size_t	len;
	char	*tmp;

	i = 0;
	len = ft_strlen(str);
	while (parse->envp[i] && ft_strncmp(parse->envp[i], str, len) != 0)
		i++;
	if (!parse->envp[i])
	{
		write(1, "\n", 1);
		return (NULL);
	}
	tmp = NULL;
	j = len - 1;
	while (parse->envp[i][j++])
		tmp = ft_stock_char(tmp, parse->envp[i][j]);
	return (tmp);
}

bool	ft_isenvvarchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

void	ft_envvar_token(int *i, t_minishell *parse)
{
	char	*tmp;

	printf(KYEL "-------------------- FT_ENVVAR --------------------\n" RESET);
	tmp = NULL;
	parse->type = EXPAND;
	while (ft_isenvvarchar(parse->input[++(*i)]))
		tmp = ft_stock_char(tmp, parse->input[(*i)]);
	if (!tmp)
	{
		tmp = ft_stock_char(tmp, '$');
		ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	}
	else
	{
		tmp = ft_stock_char(tmp, '=');
		tmp = ft_find_envvar(tmp, parse);
		if (tmp)
			ft_add_token_bottom(&parse->line, ft_create_node(tmp, parse));
	}
	ft_freenull(tmp);
	parse->type = ARG;
	parse->flag_whitespace = 0;
}

char	*ft_strjoin_free(char *str1, char *str2)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	len;

	printf("-------------------- FT_STRJOIN_FREE --------------------\n");
	if (!str1 || !str2)
		return (NULL);
	len = 0;
	len = ft_strlen(str1) + ft_strlen(str2);
	printf("len1 = %zu\n", ft_strlen(str1));
	printf("len2 = %zu\n", ft_strlen(str2));
	printf("len = %zu\n", len);
	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);
	new_str = (char *)ft_calloc((len + 1), sizeof(char));
	i = 0;
	j = 0;
	while (str1[i])
		new_str[j++] = str1[i++];
	i = 0;
	while (str2[i])
		new_str[j++] = str2[i++];
	new_str[j] = '\0';
	ft_freenull(str1);
	return (new_str);
}
