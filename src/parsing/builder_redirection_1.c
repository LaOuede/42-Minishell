#include "../../include/minishell.h"

void	ft_check_error_redir(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_REDIR" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	int		len;

	if (!pars->line)
		return ;
	ptr = pars->line;
	while (ptr)
	{
		if (ptr->type == REDIN || ptr->type == REDOUT)
		{
			len = ft_strlen(ptr->str);
			if (len > 2)
				ft_error_parsing(ERR_TOKEN, REBUILDER, pars);
		}
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CHECK_REDIR" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_angle_brackets_out(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ANGLE_BRACKETS_OUT" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	t_token	*sup;
	char	*new_str;

	ptr = pars->line;
	new_str = NULL;
	while (ptr->next)
	{
		printf("str = %s\n", ptr->str);
		printf("str next = %s\n", ptr->next->str);
		if (ptr->type == REDOUT && ptr->next->type == REDOUT)
		{
			ft_merge(ptr, ptr->next);
			sup = ptr->next;
			if (ptr->next->next)
				ptr->next = ptr->next->next;
			else if (!ptr->next->next)
				ptr->next = NULL;
			ft_free_token(sup);
		}
		else
			ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_MERGE_ANGLE_BRACKETS_OUT" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_angle_brackets_in(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ANGLE_BRACKETS_IN" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	t_token	*sup;
	char	*new_str;

	ptr = pars->line;
	new_str = NULL;
	while (ptr->next)
	{
		printf("str = %s\n", ptr->str);
		printf("str next = %s\n", ptr->next->str);
		if (ptr->type == REDIN && ptr->next->type == REDIN)
		{
			ft_merge(ptr, ptr->next);
			sup = ptr->next;
			if (ptr->next->next)
				ptr->next = ptr->next->next;
			else if (!ptr->next->next)
				ptr->next = NULL;
			ft_free_token(sup);
		}
		else
			ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_MERGE_ANGLE_BRACKETS_IN" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_redirection(t_pars *pars)
{
	ft_merge_angle_brackets_in(pars);
	ft_merge_angle_brackets_out(pars);
	ft_check_error_redir(pars);
	ft_merge_red(pars);
	ft_merge_allredin(pars);
	ft_merge_allredout(pars);
}
