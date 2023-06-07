#include "../../include/minishell.h"

void	ft_merge_pipe(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_IN" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	t_token	*sup;
	char	*new_str;

	ptr = pars->line;
	new_str = NULL;
	while (ptr->next)
	{
		printf("str = %s\n", ptr->str);
		printf("str next = %s\n", ptr->next->str);
		if (ptr->type == PIPE && ptr->next->type == PIPE)
		{
			new_str = ft_strjoin(ptr->str, ptr->next->str);
			ptr->str = ft_strdup(new_str);
			printf("new str = %s\n", ptr->str);
			ft_freenull(new_str);
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
	printf(KYEL "-------------------- FT_MERGE_IN" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_check_error_pipe(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_REDIR" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	int		len;

	if (!pars->line)
		return ;
	ptr = pars->line;
	while (ptr)
	{
		if (ptr->type == PIPE)
		{
			len = ft_strlen(ptr->str);
			if (len > 1)
				ft_error_parsing(ERR_TOKEN, REBUILDER, pars);
		}
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CHECK_REDIR" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_pipe(t_pars *pars)
{
	ft_merge_pipe(pars);
	ft_check_error_pipe(pars);
}
