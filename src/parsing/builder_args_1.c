#include "../../include/minishell.h"

void	ft_merge_all_arg(t_ms *ms)
{
	t_token	*ptr1;
	t_token	*ptr2;

	ptr1 = ms->pars->line;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != PIPE)
		{
			if ((ptr1->type == ARG || ptr1->type == CMD \
				|| ptr1->type == ACCESS_ERR) && ptr2->type == ARG)
			{
				if (ptr2->ws == 1)
					ptr1->str = ft_strjoin_char(ms, ptr1->str, 29);
				ft_merge(ptr1, ptr2);
				ptr2->type = ERROR;
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}

bool	ft_test_cmd(t_pars *pars, t_token *node)
{
	int		i;
	char	*path;

	if (access(node->str, F_OK | X_OK) == 0)
		return (true);
	path = ft_strjoin("./", node->str);
	if (access(path, F_OK | X_OK) == 0)
	{
		path = ft_freenull(path);
		return (true);
	}
	if (path)
		path = ft_freenull(path);
	i = -1;
	while (pars->path_var[++i])
	{
		path = ft_strjoin(pars->path_var[i], node->str);
		if (access(path, F_OK | X_OK) == 0)
		{
			path = ft_freenull(path);
			return (true);
		}
		path = ft_freenull(path);
	}
	return (false);
}

/*
Identify the first ARG token as CMD
*/
void	ft_find_cmd(t_ms *ms)
{
	bool	flag;
	t_token	*ptr;

	flag = true;
	ptr = ms->pars->line;
	while (ptr)
	{
		if (ptr->type == ARG && flag == true)
		{
			ptr->type = CMD;
			ft_lower_cmd(ptr->str);
			if ((ft_bi(ptr) == false) && (ft_test_cmd(ms->pars, ptr) == false))
			{
				printf(ERR_ACCESS);
				ms->flexit = 127;
				ptr->type = ACCESS_ERR;
				ptr->str = ft_freenull(ptr->str);
				ptr->str = ft_strdup("ERROR");
			}
			flag = false;
		}
		else if (ptr->type == PIPE)
			flag = true;
		ptr = ptr->next;
	}
}

/*
Merge all ARG type tokens with no whitespace flag
*/
void	ft_merge_arg(t_pars *pars)
{
	t_token	*ptr1;
	t_token	*ptr2;

	ptr1 = pars->line;
	ptr2 = pars->line;
	while (ptr1->next)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != PIPE)
		{
			if (ptr1->type == ARG && ptr2->type == ARG \
				&& (ptr2->ws == 0 && ptr2->str[0] != 29))
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
}

void	ft_args(t_ms *ms)
{
	ft_merge_arg(ms->pars);
	ft_find_cmd(ms);
	ft_merge_all_arg(ms);
	ft_check_access(ms);
}
