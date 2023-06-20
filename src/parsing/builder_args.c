#include "../../include/minishell.h"

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
	printf(KYEL "-------------------- FT_MERGE_ALL_ARG" KRED " END " RESET KYEL "--------------------\n" RESET);
}

bool	ft_test_cmd(t_pars *pars, t_token *node)
{
	char	*path;
	int		i;

	if (access(node->str, F_OK | X_OK) == 0)
		return (true);
	path = ft_strjoin("./", node->str);
	if (access(path, F_OK | X_OK) == 0)
		return (true);
	if (path)
		free(path);
	i = -1;
	while (pars->path_var[++i])
	{
		path = ft_strjoin(pars->path_var[i], node->str);
		if (access(path, F_OK | X_OK) == 0)
			return (true);
		if (path)
			free(path);
	}
	path = NULL;
	return (false);
}

/*
Identify the first ARG token as CMD
*/
void	ft_find_cmd(t_pars *pars)
{
	printf(KYEL "-------------------- FT_FIND_CMD" KGRN " START " RESET KYEL "--------------------\n" RESET);
	bool	flag;
	t_token	*ptr;

	flag = true;
	ptr = pars->line;
	while (ptr)
	{
		printf("ptr->type before = %d\n", ptr->type);
		if (ptr->type == ARG && flag == true)
		{
			ptr->type = CMD;
			if (ft_test_cmd(pars, ptr) == false)
				ptr->type = ACCESS_ERR;
			if (ptr->type == ACCESS_ERR && pars->nb_pipe == 1)
				ft_error_parsing(ERR_ACCESS, PARSER, 127, pars);
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

/*
Merge all ARG type tokens with no whitespace flag
*/
void	ft_merge_arg(t_pars *pars)
{
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
	printf(KYEL "-------------------- FT_MERGE_ARG" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_args(t_pars *pars)
{
	ft_merge_arg(pars);
	ft_find_cmd(pars);
	ft_merge_all_arg(pars);
}
