#include "../../include/minishell.h"

void	ft_clean_list(t_token **list)
{
	printf(KYEL "-------------------- FT_CLEAN_LIST" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token *sup;
	t_token	*ptr;

	if (!list || !*list)
		return ;
	ptr = *list;
	while (ptr->next)
	{
		printf("ptr->next->type = %d\n", ptr->next->type);
		printf("ptr->next->str = %p\n", ptr->next->str);
		if (ptr->next->type == ERROR)
		{
			sup = ptr->next;
			if (ptr->next->next)
				ptr->next = ptr->next->next;
			else if (!ptr->next->next)
				ptr->next = NULL;
			printf("sup->str = %s\n", sup->str);
			printf("sup->str = %p\n", sup->str);
			ft_free_token(sup);
		}
		else
			ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CLEAN_LIST" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_swap(t_pars *pars)
{
	printf(KYEL "-------------------- FT_SWAP" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;
	int		swap;
	char	*str;

	if (!pars->line)
		return ;
	ptr1 = pars->line;
	ptr2 = ptr1;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != 4)
		{
			if (ptr1->type > ptr2->type && ptr1->type != PIPE && ptr2->type != PIPE)
			{
				swap = ptr1->type;
				ptr1->type = ptr2->type;
				ptr2->type = swap;
				str = ptr1->str;
				ptr1->str = ptr2->str;
				ptr2->str = str;
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	printf(KYEL "-------------------- FT_SWAP" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_finish(t_pars *pars)
{
	ft_clean_list(&pars->line);
	ft_swap(pars);
}
