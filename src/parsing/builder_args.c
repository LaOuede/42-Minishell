#include "../../include/minishell.h"

/*
Check for REDIN or REDOUT token at the end of the linked-list.
*/
void	ft_check_access(t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_ACCESS" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	int		counter;

	counter = 0;
	ptr = ms->pars->line;
	while (ptr)
	{
		if (DEBUG)
			printf("ptr->srt = %s\n", ptr->str);
		if (ptr->type == ACCESS_ERR)
			counter += 1;
		ptr = ptr->next;
	}
	if (DEBUG)
		printf("counter = %d\n", counter);
	if (counter == ms->pars->nb_pipe)
		ft_error_parsing(0, PARSER, 127, ms);
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_ACCESS" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_all_arg(t_pars *pars)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_MERGE_ALL_ARG" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;

	ptr1 = pars->line;
	ptr2 = pars->line;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != PIPE)
		{
			if ((ptr1->type == ARG || ptr1->type == CMD || ptr1->type == ACCESS_ERR) && ptr2->type == ARG)
			{
				if (ptr2->ws == 1)
					ptr1->str = ft_strjoin_char(ptr1->str, ' ');
				ft_merge(ptr1, ptr2);
				ptr2->type = ERROR;
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_MERGE_ALL_ARG" KRED " END " RESET KYEL "--------------------\n" RESET);
}

bool	ft_bi(t_token *node)
{
	if ((ft_strcmp(node->str, "exit") == 0) || (ft_strcmp(node->str, "unset") == 0) || (ft_strcmp(node->str, "export") == 0))
		return (true);
	return (false);
}

void	ft_lower_cmd(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);

}

/*
Identify the first ARG token as CMD
*/
void	ft_find_cmd(t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_FIND_CMD" KGRN " START " RESET KYEL "--------------------\n" RESET);
	bool	flag;
	t_token	*ptr;

	flag = true;
	ptr = ms->pars->line;
	while (ptr)
	{
		if (DEBUG)
			printf("ptr->type before = %d\n", ptr->type);
		if (ptr->type == ARG && flag == true)
		{
			ptr->type = CMD;
			ft_lower_cmd(ptr->str);
			printf("ptr->str %s\n", ptr->str);
			if ((ft_bi(ptr) == false) && (ft_test_cmd(ms->pars, ptr) == false))
			{
				printf(ERR_ACCESS);
				ms->flexit = 127;
				ptr->type = ACCESS_ERR;
				ft_freenull(ptr->str);
				ptr->str = ft_strdup("ERROR");
			}
			flag = false;
		}
		else if (ptr->type == PIPE)
			flag = true;
		if (DEBUG)
		{
			printf("ptr->type after = %d\n", ptr->type);
			printf("flag = %d\n", flag);
		}
		ptr = ptr->next;
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_FIND_CMD" KRED " END " RESET KYEL "--------------------\n" RESET);
}

/*
Merge all ARG type tokens with no whitespace flag
*/
void	ft_merge_arg(t_pars *pars)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_MERGE_ARG" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;

	ptr1 = pars->line;
	ptr2 = pars->line;
	while (ptr1->next)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != PIPE)
		{
			if (ptr1->type == ARG && ptr2->type == ARG && ptr2->ws == 0)
			{
				ft_merge(ptr1, ptr2);
				ptr2->type = ERROR;
				ptr2 = ptr2->next;
			}
			else
				break ;
		}
		ptr1 = ptr1->next;
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_MERGE_ARG" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_args(t_ms *ms)
{
	ft_merge_arg(ms->pars);
	ft_find_cmd(ms);
	ft_merge_all_arg(ms->pars);
	ft_check_access(ms);
}
