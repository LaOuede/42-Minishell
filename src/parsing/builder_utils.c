#include "../../include/minishell.h"

void	ft_merge_all_red(t_ms *ms)
{
	t_token	*ptr1;
	t_token	*ptr2;

	ptr1 = ms->pars->line;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != PIPE)
		{
			if (ptr1->type == REDOUT && ptr2->type == REDOUT)
			{
				ptr1->str = ft_strjoin_char(ms, ptr1->str, ' ');
				ft_merge(ptr1, ptr2);
				ptr2->type = ERROR;
			}
			else if (ptr1->type == REDIN && ptr2->type == REDIN)
			{
				ptr1->str = ft_strjoin_char(ms, ptr1->str, ' ');
				ft_merge(ptr1, ptr2);
				ptr2->type = ERROR;
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}

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
