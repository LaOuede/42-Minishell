#include "../../include/minishell.h"

void	ft_check_error_pipe(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_ERROR_PIPE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;

	ptr = pars->line;
	if (ptr->type == PIPE)
		ft_error_parsing(ERR_TOKEN, REBUILDER, pars);
	while (ptr->next)
	{
		printf("str = %s\n", ptr->str);
		printf("str next = %s\n", ptr->next->str);
		if (ptr->type == PIPE && ptr->next->type == PIPE)
		{
			ft_error_parsing(ERR_TOKEN, REBUILDER, pars);
			break ;
		}
		else
			ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CHECK_ERROR_PIPE" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_clean_list(t_token **list)
{
	printf(KYEL "-------------------- FT_CLEAN_LIST" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*sup;
	t_token	*ptr;

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

void	ft_swap(t_token *ptr1, t_token *ptr2)
{
	char	*str;
	int		swap;

	swap = ptr1->type;
	ptr1->type = ptr2->type;
	ptr2->type = swap;
	str = ptr1->str;
	ptr1->str = ptr2->str;
	ptr2->str = str;
}

void	ft_swap_node(t_pars *pars)
{
	printf(KYEL "-------------------- FT_SWAP" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;

	ptr1 = pars->line;
	ptr2 = ptr1;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != 4)
		{
			if (ptr1->type > ptr2->type && ptr1->type != PIPE \
				&& ptr2->type != PIPE)
				ft_swap(ptr1, ptr2);
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	printf(KYEL "-------------------- FT_SWAP" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_cleaning(t_pars *pars)
{
	ft_check_error_pipe(pars);
	ft_clean_list(&pars->line);
	ft_swap_node(pars);
}
