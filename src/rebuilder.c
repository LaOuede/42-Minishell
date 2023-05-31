#include "../include/minishell.h"

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

void	ft_find_redout(t_pars *pars)
{
	printf(KYEL "-------------------- FT_FIND_REDOUT" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	bool	flag;

	ptr = pars->line;
	flag = true;
	while (ptr)
	{
		if ((ptr->type == REDOUT || ptr->type == HEREDOC) && flag == true)
			flag = false;
		else if ((ptr->type == REDOUT || ptr->type == HEREDOC) && flag == false)
			ptr->type = ERROR;
		if (ptr->type == PIPE)
			flag = true;
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_FIND_REDOUT" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_find_redin(t_pars *pars)
{
	printf(KYEL "-------------------- FT_FIND_REDIN" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	bool	flag;

	ptr = pars->line;
	flag = true;
	while (ptr)
	{
		if ((ptr->type == REDIN || ptr->type == APPRED) && flag == true)
			flag = false;
		else if ((ptr->type == REDIN || ptr->type == APPRED) && flag == false)
			ptr->type = ERROR;
		if (ptr->type == PIPE)
			flag = true;
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_FIND_REDIN" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_find_arg(t_pars *pars)
{
	printf(KYEL "-------------------- FT_FIND_CMD" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	bool	flag;

	ptr = pars->line;
	flag = true;
	while (ptr)
	{
		if ((ptr->type == ARG || ptr->type == EXPAND) && flag == true)
			flag = false;
		else if (ptr->type == ARG && flag == false)
			ptr->type = ERROR;
		if (ptr->type == PIPE)
			flag = true;
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_FIND_CMD" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_find_cmd(t_pars *pars)
{
	printf(KYEL "-------------------- FT_FIND_CMD" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	bool	flag;

	ptr = pars->line;
	flag = true;
	while (ptr)
	{
		if ((ptr->type == ARG || ptr->type == EXPAND) && flag == true)
		{
			ptr->type = CMD;
			flag = false;
		}
		if (ptr->type == PIPE)
			flag = true;
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_FIND_CMD" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_allredin(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ALLREDIN" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;
	char	*new_str;

	if (!pars->line)
		return ;
	ptr1 = pars->line;
	ptr2 = ptr1;
	new_str = ft_calloc(1, sizeof(char));
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != 4)
		{
			if ((ptr1->type == 5 || ptr1->type == 6 ) && (ptr2->type == 5 || ptr2->type == 6))
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
				ptr1->str = ft_strdup(new_str);
				ft_freenull(new_str);
				printf("new_str = %s\n", new_str);
				printf("ptr->str = %s\n", ptr1->str);
				printf("ptr->next->str = %s\n", ptr2->str);
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	printf(KYEL "-------------------- FT_MERGE_ALLREDIN" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_allredout(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ALLREDOUT" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;
	char	*new_str;

	if (!pars->line)
		return ;
	ptr1 = pars->line;
	ptr2 = ptr1;
	new_str = ft_calloc(1, sizeof(char));
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != 4)
		{
			if ((ptr1->type == 7 || ptr1->type == 8 ) && (ptr2->type == 7 || ptr2->type == 8))
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
				ptr1->str = ft_strdup(new_str);
				ft_freenull(new_str);
				printf("new_str = %s\n", new_str);
				printf("ptr->str = %s\n", ptr1->str);
				printf("ptr->next->str = %s\n", ptr2->str);
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	printf(KYEL "-------------------- FT_MERGE_ALLREDOUT" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_red(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_RED" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	t_token	*sup;
	char	*new_str;

	if (!pars->line)
		return ;
	ptr = pars->line;
	new_str = ft_calloc(1, sizeof(char));
/* 	printf("str = %s\n", ptr->str);
	printf("str next = %s\n", ptr->next->str);
	printf("ptr->type = %d\n", ptr->type); */
	while (ptr->next)
	{
		if (5 <= ptr->type && ptr->type <= 8 && ptr->next->type < 4)
		{
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
/* 			printf("new_str = %s\n", new_str);
			printf("ptr->str = %s\n", ptr->str);
			printf("ptr->next->str = %s\n", ptr->next->str); */
			sup = ptr->next;
			if (ptr->next->next)
			{
				printf("test1\n");
				ptr->next = ptr->next->next;
			}
			else if (!ptr->next->next)
			{
				printf("test2\n");
				ptr->next = NULL;
			}
			ft_free_token(sup);
			printf("sup->str = %s\n", sup->str);
		}
		if (ptr->next)
			ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_MERGE_RED" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_arg(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ARG" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;
	char	*new_str;

	if (!pars->line)
		return ;
	ptr1 = pars->line;
	ptr2 = ptr1;
	new_str = ft_calloc(1, sizeof(char));
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != 4)
		{
			if ((0 <= ptr1->type && ptr1->type <= 3) && (0 <= ptr2->type && ptr2->type <= 3))
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
				ptr1->str = ft_strdup(new_str);
				ft_freenull(new_str);
				printf("new_str = %s\n", new_str);
				printf("ptr->str = %s\n", ptr1->str);
				printf("ptr->next->str = %s\n", ptr2->str);
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	printf(KYEL "-------------------- FT_MERGE_ARG" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_rebuilder(t_pars *pars)
{
	printf(KYEL "-------------------- FT_REBUILDER" KGRN " START " RESET KYEL "--------------------\n" RESET);
	ft_merge_red(pars);
	ft_merge_allredin(pars);
	ft_merge_allredout(pars);
	ft_find_cmd(pars);
	ft_merge_arg(pars);
	ft_find_arg(pars);
	ft_find_redin(pars);
	ft_find_redout(pars);
	ft_clean_list(&pars->line);
	ft_swap(pars);
	printf(KYEL "-------------------- FT_REBUILDER" KRED " END " RESET KYEL "--------------------\n" RESET);
}
