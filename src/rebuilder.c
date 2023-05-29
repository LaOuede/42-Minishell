#include "../include/minishell.h"

/* void	ft_merge_arg(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ARG" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	t_token *sup;
	char	*new_str;

	new_str = ft_calloc(1, sizeof(char));
	printf("str = %s\n", pars->line->str);
	printf("str next = %s\n", pars->line->next->str);
	while (pars->line->next && (0 <= pars->line->type && pars->line->type <= 3) && (0 <= pars->line->next->type && pars->line->next->type <= 3))
	{
		if (pars->line->str && !pars->line->next->str)
			new_str = ft_strdup(pars->line->str);
		else if (!pars->line->str && pars->line->next->str)
			new_str = ft_strdup(pars->line->next->str);
		else if (pars->line->str && pars->line->next->str)
			new_str = ft_strjoin(pars->line->str, pars->line->next->str);
		pars->line->str = ft_strdup(new_str);
		ft_freenull(new_str);
		printf("new_str = %s\n", new_str);
		printf("pars->line->str = %s\n", pars->line->str);
		printf("pars->line->next->str = %s\n", pars->line->next->str);
		sup = pars->line->next;
		ft_free_token(sup);
		printf("sup->str = %s\n", sup->str);
		pars->line->next = pars->line->next->next;
	}
	if (pars->line->next && pars->line->type == 4)
		pars->line->next = pars->line->next->next;
	
	printf(KYEL "-------------------- FT_MERGE_ARG" KRED " END " RESET KYEL "--------------------\n" RESET);
} */

void	ft_merge_arg(t_token **list)
{
	printf(KYEL "-------------------- FT_MERGE_ARG" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	t_token *sup;
	t_token	*ptr;
	char	*new_str;

	ptr = *list;
	new_str = ft_calloc(1, sizeof(char));
	printf("str = %s\n", ptr->str);
	printf("str next = %s\n", ptr->next->str);
	while (ptr->next && (0 <= ptr->type && ptr->type <= 3) && (0 <= ptr->next->type && ptr->next->type <= 3))
	{
		if (ptr->str && !ptr->next->str)
			new_str = ft_strdup(ptr->str);
		else if (!ptr->str && ptr->next->str)
			new_str = ft_strdup(ptr->next->str);
		else if (ptr->str && ptr->next->str)
			new_str = ft_strjoin(ptr->str, ptr->next->str);
		ptr->str = ft_strdup(new_str);
		ft_freenull(new_str);
		printf("new_str = %s\n", new_str);
		printf("ptr->str = %s\n", ptr->str);
		printf("ptr->next->str = %s\n", ptr->next->str);
		sup = ptr->next;
		ft_free_token(sup);
		printf("sup->str = %s\n", sup->str);
		ptr->next = ptr->next->next;
	}
	printf(KYEL "-------------------- FT_MERGE_ARG" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_rebuilder(t_pars *pars)
{
	printf(KYEL "-------------------- FT_REBUILDER" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	t_token *tmp;

	tmp = pars->line;
	while (tmp->next)
	{
		printf("TEST\n");
		if (tmp && (0 <= tmp->type && tmp->type <= 3))
			ft_merge_arg(&tmp);
		//else if (tmp && (5 <= tmp->type && tmp->type <= 8)
		if (tmp->next)
			tmp = tmp->next;
	}
	printf(KYEL "-------------------- FT_REBUILDER" KRED " END " RESET KYEL "--------------------\n" RESET);
}
