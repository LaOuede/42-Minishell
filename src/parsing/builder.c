#include "../../include/minishell.h"

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
	ft_args(pars);
	ft_end_builder(pars);
	printf(KYEL "-------------------- FT_BUILDER" KRED " END " RESET KYEL "--------------------\n" RESET);
}
