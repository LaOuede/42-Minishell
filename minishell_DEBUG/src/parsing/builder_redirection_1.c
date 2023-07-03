#include "../../include/minishell.h"

bool	ft_test_cmd(t_pars *pars, t_token *node)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_TEST_CMD --------------------\n" RT);
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

void	ft_check_error_redir(t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_ERROR_REDIR" KGRN " START " RT KYEL "--------------------\n" RT);
	int		len;
	t_token	*ptr;

	if (!ms->pars->line)
		return ;
	ptr = ms->pars->line;
	while (ptr)
	{
		if (ptr->type == REDIN || ptr->type == REDOUT)
		{
			len = ft_strlen(ptr->str);
			if (ms->pars->fl_red == false && (len > 2 || (ptr->next && ptr->next->type == REDIN) \
				|| (ptr->next && ptr->next->type == REDOUT)))
			{
				ms->pars->fl_red = true;
				ft_error_parsing(ERR_TOKEN, REBUILDER, 258, ms);
			}
			else if (ms->pars->fl_red == 0 && (!ptr->next || ptr->next->str[0] == 29))
			{
				ms->pars->fl_red = true;
				ft_error_parsing(ERR_TOKEN, REBUILDER, 258, ms);
			}
		}
		ptr = ptr->next;
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_ERROR_REDIR" KRED " END " RT KYEL "--------------------\n" RT);
}

void	ft_merge_angle_brackets_out(t_pars *pars)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_MERGE_ANGLE_BRACKETS_OUT" KGRN " START " RT KYEL "--------------------\n" RT);
	t_token	*ptr;
	t_token	*sup;

	ptr = pars->line;
	while (ptr->next)
	{
		if (DEBUG){
			printf("str = %s\n", ptr->str);
			printf("str next = %s\n", ptr->next->str);
		}
		if (ptr->next->ws == 0 && ptr->type == REDOUT && ptr->next->type == REDOUT)
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
	if (DEBUG)
		printf(KYEL "-------------------- FT_MERGE_ANGLE_BRACKETS_OUT" KRED " END " RT KYEL "--------------------\n" RT);
}

void	ft_merge_angle_brackets_in(t_pars *pars)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_MERGE_ANGLE_BRACKETS_IN" KGRN " START " RT KYEL "--------------------\n" RT);
	t_token	*ptr;
	t_token	*sup;

	ptr = pars->line;
	while (ptr->next)
	{
		if (DEBUG)
		{
			printf("str = %s\n", ptr->str);
			printf("str next = %s\n", ptr->next->str);
		}
		if (ptr->next->ws == 0 && ptr->type == REDIN && ptr->next->type == REDIN)
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
	if (DEBUG)
		printf(KYEL "-------------------- FT_MERGE_ANGLE_BRACKETS_IN" KRED " END " RT KYEL "--------------------\n" RT);
}

/*
1) Merge redirection token.
2) Check for error (eg. >>>).
3) Try to open all the REDIN files.
4) Create all the REDOUT files.
5) Merge all redirection tokens.
*/
void	ft_redirection(t_ms *ms)
{
	ms->jct->fds_in = ft_calloc_msh(ms->pars->nb_pipe, sizeof(int), ms);
	ms->jct->fds_out = ft_calloc_msh(ms->pars->nb_pipe, sizeof(int), ms);
	ft_merge_angle_brackets_in(ms->pars);
	ft_merge_angle_brackets_out(ms->pars);
	ft_check_error_redir(ms);
	if (ms->pars->err_builder == false)
	{
		ft_open_hd(ms);
		ft_open_file(ms);
		if (ms->pars->err_infile == false)
			ft_create_file(ms);
		ft_merge_red(ms);
		ft_merge_all_red(ms);
	}
}
