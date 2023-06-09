#include "../../include/minishell.h"

void	ft_find_arg(t_pars *pars)
{
	printf(KYEL "-------------------- FT_FIND_ARG" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	bool	flag;

	ptr = pars->line;
	flag = true;
	while (ptr)
	{
		printf("flag = %d\n", flag);
		printf("str = %s\n", ptr->str);
		printf("str->type before= %d\n", ptr->type);
		if (ptr->type == ARG && flag == true)
			flag = false;
		else if (ptr->type == ARG && flag == false)
			ptr->type = ERROR;
		if (ptr->type == PIPE)
			flag = true;
		printf("str->type after = %d\n", ptr->type);
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_FIND_ARG" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_all_arg(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ALL_ARG" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;

	ptr1 = pars->line;
	ptr2 = pars->line;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != 4)
		{
			if (ptr1->type == ARG && ptr2->type == ARG)
				ft_merge(ptr1, ptr2);
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	printf(KYEL "-------------------- FT_MERGE_ALL_ARG" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_arg(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ARG" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;
	char	*new_str;
	char	*tmp;

	if (!pars->line)
		return ;
	ptr1 = pars->line;
	ptr2 = pars->line;
	new_str = NULL;
	tmp = NULL;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != 4)
		{
			if (ptr1->type == ARG && ptr2->type == ARG && ptr2->ws == 0)
			{
				if (ptr1->str && !ptr2->str)
					new_str = ft_strdup(ptr1->str);
				else if (!ptr1->str && ptr2->str)
					new_str = ft_strdup(ptr2->str);
				else if (ptr1->str && ptr2->str)
				{
					if (ptr2->ws == 1)
						ptr1->str = ft_strjoin_char(ptr1->str, ' ');
					new_str = ft_strjoin(ptr1->str, ptr2->str);
				}
				tmp = ptr1->str;
				ptr1->str = ft_strdup(new_str);
				ptr1->next->type = ERROR;
				ft_freenull(tmp);
				ft_freenull(new_str);
				printf("ptr->str = %s\n", ptr1->str);
				printf("ptr->next->str = %s\n", ptr2->str);
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	printf(KYEL "-------------------- FT_MERGE_ARG" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_args(t_pars *pars)
{
	ft_merge_arg(pars);
	ft_find_cmd(pars);
	ft_merge_all_arg(pars);
	ft_find_arg(pars);
}
