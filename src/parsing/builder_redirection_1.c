#include "../../include/minishell.h"

bool	ft_test_cmd(t_pars *pars, t_token *node)
{
	printf(KYEL "-------------------- FT_TEST_CMD --------------------\n" RESET);
	int		i;
	char	*path;

	if (access(node->str, F_OK | X_OK) == 0)
		return (true);
	path = ft_strjoin("./", node->str);
	if (access(path, F_OK | X_OK) == 0)
	{
		ft_freenull(path);
		return (true);
	}
	if (path)
		ft_freenull(path);
	i = -1;
	while (pars->path_var[++i])
	{
		path = ft_strjoin(pars->path_var[i], node->str);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_freenull(path);
			return (true);
		}
		if (path)
			ft_freenull(path);
	}
	path = NULL;
	return (false);
}

void	ft_check_error_redir(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_REDIR" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int		len;
	t_token	*ptr;

	if (!pars->line)
		return ;
	ptr = pars->line;
	while (ptr)
	{
		if (ptr->type == REDIN || ptr->type == REDOUT)
		{
			len = ft_strlen(ptr->str);
			if (len > 2)
				ft_error_parsing(ERR_TOKEN, REBUILDER, 2, pars);
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

	ptr = pars->line;
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

	ptr = pars->line;
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

/*
1) Merge redirection token.
2) Check for error (eg. >>>).
3) Try to open all the REDIN files.
4) Create all the REDOUT files.
5) Merge all redirection tokens.
*/
void	ft_redirection(t_pars *pars)
{
	pars->jct->fds_in = ft_calloc(pars->nb_pipe, sizeof(int));
	pars->jct->fds_out = ft_calloc(pars->nb_pipe, sizeof(int));
	ft_merge_angle_brackets_in(pars);
	ft_merge_angle_brackets_out(pars);
	ft_check_error_redir(pars);
	ft_open_file(pars);
	if (pars->err_infile == false)
		ft_create_file(pars);
	ft_merge_red(pars);
	ft_merge_allredin(pars);
	ft_merge_allredout(pars);
}
