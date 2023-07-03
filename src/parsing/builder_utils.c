#include "../../include/minishell.h"

bool	ft_bi(t_token *node)
{
	if ((ft_strcmp(node->str, "exit") == 0) \
		|| (ft_strcmp(node->str, "unset") == 0) \
		|| (ft_strcmp(node->str, "export") == 0))
		return (true);
	return (false);
}

void	ft_lower_cmd(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
}
