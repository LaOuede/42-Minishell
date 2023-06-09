#include "../../include/minishell.h"

void	ft_find_redout(t_pars *pars)
{
	printf(KYEL "-------------------- FT_FIND_REDOUT" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	bool	flag;

	ptr = pars->line;
	flag = true;
	while (ptr)
	{
		if (ptr->type == REDOUT && flag == true)
			flag = false;
		else if (ptr->type == REDOUT && flag == false)
			ptr->type = ERROR;
		if (ptr->type == PIPE)
			flag = true;
		printf("ptr->type = %d\n", ptr->type);
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
		if (ptr->type == REDIN && flag == true)
			flag = false;
		else if (ptr->type == REDIN && flag == false)
			ptr->type = ERROR;
		if (ptr->type == PIPE)
			flag = true;
		printf("ptr->type = %d\n", ptr->type);
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_FIND_REDIN" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge(t_token *node, t_token *next)
{
	printf(KYEL "-------------------- FT_MERGE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	tmp = NULL;
	new_str = ft_strjoin(node->str, next->str);
	tmp = node->str;
	node->str = ft_strdup(new_str);
	ft_freenull(tmp);
	ft_freenull(new_str);
	printf("ptr->str = %s\n", node->str);
	printf("ptr->next->str = %s\n", next->str);
	printf(KYEL "-------------------- FT_MERGE" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_builder(t_pars *pars)
{
	printf(KYEL "-------------------- FT_BUILDER" KGRN " START " RESET KYEL "--------------------\n" RESET);
	ft_redirection(pars);
	ft_find_redin(pars);
	ft_find_redout(pars);
	ft_args(pars);
	ft_cleaning(pars);
	printf(KYEL "-------------------- FT_BUILDER" KRED " END " RESET KYEL "--------------------\n" RESET);
}
