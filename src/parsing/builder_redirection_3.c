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

void	ft_merge_red(t_ms *ms)
{
	t_token	*ptr;
	t_token	*sup;

	ptr = ms->pars->line;
	sup = NULL;
	while (ptr->next)
	{
		if ((ptr->type == REDIN || ptr->type == REDOUT) \
			&& ptr->next->type == ARG)
		{
			ptr->str = ft_strjoin_char(ms, ptr->str, ' ');
			ft_merge(ptr, ptr->next);
			sup = ptr->next;
			if (ptr->next->next)
				ptr->next = ptr->next->next;
			else if (!ptr->next->next)
				ptr->next = NULL;
			ft_free_token(sup);
		}
		if (ptr->next)
			ptr = ptr->next;
	}
}
