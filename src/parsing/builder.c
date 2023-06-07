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

void	ft_find_cmd(t_pars *pars)
{
	printf(KYEL "-------------------- FT_FIND_CMD" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	bool	flag;

	ptr = pars->line;
	flag = true;
	while (ptr)
	{
		printf("ptr->type before = %d\n", ptr->type);
		if (ptr->type == ARG && flag == true)
		{
			ptr->type = CMD;
			flag = false;
		}
		else if (ptr->type == PIPE)
			flag = true;
		printf("ptr->type after = %d\n", ptr->type);
		printf("flag = %d\n", flag);
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_FIND_CMD" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_builder(t_pars *pars)
{
	printf(KYEL "-------------------- FT_REBUILDER" KGRN " START " RESET KYEL "--------------------\n" RESET);
	ft_pipe(pars);
	ft_redirection(pars);
	ft_find_cmd(pars);
	ft_args(pars);
	ft_find_redin(pars);
	ft_find_redout(pars);
	printf(KYEL "-------------------- FT_REBUILDER" KRED " END " RESET KYEL "--------------------\n" RESET);
}
