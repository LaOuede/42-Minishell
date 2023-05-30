#include "../include/minishell.h"

void	ft_remove_empty(t_token **list)
{
	printf(KYEL "-------------------- FT_REMOVE_EMPTY" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token *sup;
	t_token	*ptr;

	ptr = *list;
	while (ptr)
	{
		if (!ptr->str)
		{
			sup = ptr;
			ft_free_token(sup);
		}
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_REMOVE_EMPTY" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_red(t_token **list)
{
	printf(KYEL "-------------------- FT_MERGE_RED" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token *sup;
	t_token	*ptr;
	char	*new_str;

	ptr = *list;
	new_str = ft_calloc(1, sizeof(char));
	printf("str = %s\n", ptr->str);
	printf("str next = %s\n", ptr->next->str);
	printf("ptr->type = %d\n", ptr->type);
	if (ptr->str && !ptr->next->str)
		new_str = ft_strdup(ptr->str);
	else if (!ptr->str && ptr->next->str)
		new_str = ft_strdup(ptr->next->str);
	else if (ptr->str && ptr->next->str)
	{
		ptr->str = ft_strjoin_char(ptr->str, ' ');
		new_str = ft_strjoin(ptr->str, ptr->next->str);
	}
	ptr->str = ft_strdup(new_str);
	ft_freenull(new_str);
	printf("new_str = %s\n", new_str);
	printf("ptr->str = %s\n", ptr->str);
	printf("ptr->next->str = %s\n", ptr->next->str);
	sup = ptr->next;
	ft_free_token(sup);
	printf("sup->str = %s\n", sup->str);
	ptr->next = ptr->next->next;
	printf(KYEL "-------------------- FT_MERGE_RED" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_arg(t_token **list)
{
	printf(KYEL "-------------------- FT_MERGE_ARG" KGRN " START " RESET KYEL "--------------------\n" RESET);
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
		{
			if (ptr->next->ws == 1)
				ptr->str = ft_strjoin_char(ptr->str, ' ');
			new_str = ft_strjoin(ptr->str, ptr->next->str);
		}
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
	printf(KYEL "-------------------- FT_REBUILDER" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token *tmp;

	tmp = pars->line;
	if (!pars->line)
		return ;
	while (tmp->next)
	{
		printf("TEST\n");
		if (tmp && (0 <= tmp->type && tmp->type <= 3))
			ft_merge_arg(&tmp);
		else if (tmp && (5 <= tmp->type && tmp->type <= 8))
			ft_merge_red(&tmp);
		if (tmp->next)
			tmp = tmp->next;
	}
/* 	tmp = pars->line;
	ft_remove_empty(&tmp); */
	printf(KYEL "-------------------- FT_REBUILDER" KRED " END " RESET KYEL "--------------------\n" RESET);
}
