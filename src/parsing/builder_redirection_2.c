#include "../../include/minishell.h"

void	ft_merge_all_red(t_pars *pars)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_MERGE_ALLREDOUT" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;

	ptr1 = pars->line;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != PIPE)
		{
			if (ptr1->type == REDOUT && ptr2->type == REDOUT)
			{
				ptr1->str = ft_strjoin_char(ptr1->str, ' ');
				ft_merge(ptr1, ptr2);
				ptr2->type = ERROR;
			}
			else if (ptr1->type == REDIN && ptr2->type == REDIN)
			{
				ptr1->str = ft_strjoin_char(ptr1->str, ' ');
				ft_merge(ptr1, ptr2);
				ptr2->type = ERROR;
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_MERGE_ALLREDOUT" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_creation(t_ms *ms,t_token ptr, char *str, int *i)
{
	if (DEBUG)
	{
		printf("file name = %s\n", ptr.next->str);
		printf("ptr.str = %s\n", ptr.str);
	}
	if (ms->jct->fds_out[*i])
		close(ms->jct->fds_out[*i]);
	if (ft_strncmp(ptr.str, str, 2) == 0)
		ms->jct->fds_out[*i] = open(ptr.next->str, \
			O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		ms->jct->fds_out[*i] = open(ptr.next->str, \
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (ms->jct->fds_out[*i] == -1)
		ft_error_parsing(ERR_OUTFILE, REBUILDER, 1, ms);
	if (DEBUG)
		printf("ms->pars->jct->fds_out[%d] : %d\n", *i, ms->jct->fds_out[*i]);
}

void	ft_create_file(t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CREATE_FILE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int		i;
	char	*str;
	t_token	*ptr;

	i = 0;
	str = ">>";
	ptr = ms->pars->line;
	while (ptr->next)
	{
		if (ptr->type == REDOUT && ptr->next->type == ARG)
			ft_creation(ms, *ptr, str, &i);
		else if (ptr->type == PIPE)
			i++;
		ptr = ptr->next;
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_CREATE_FILE" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_open_file(t_ms *ms)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_OPEN_FILE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int		i;
	char	*str;
	t_token	*ptr;

	i = 0;
	str = "<<";
	ptr = ms->pars->line;
	while (ptr->next)
	{
		if (ptr->type == REDIN && ptr->next->type == ARG)
		{
			if (DEBUG)
				printf("file name or delimiter = %s\n", ptr->next->str);
			if (ms->jct->fds_in[i])
				close(ms->jct->fds_in[i]);
			if (ft_strncmp(ptr->str, str, 2) == 0)
				ft_exec_hd(ptr->next->str, ms);
			else
				ms->jct->fds_in[i] = open(ptr->next->str, O_RDONLY);
			if (ms->jct->fds_in[i] == -1)
			{
				ft_error_parsing(ERR_INFILE, REBUILDER, 2, ms);
				ms->pars->err_infile = true;
				break ;
			}
			if (DEBUG)
				printf("ms->pars->jct->fds_in[i] = %d\n", ms->jct->fds_in[i]);
		}
		else if (ptr->type == PIPE)
			i++;
		ptr = ptr->next;
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_OPEN_FILE" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_red(t_pars *pars)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_MERGE_RED" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	t_token	*sup;

	ptr = pars->line;
	sup = NULL;
	while (ptr->next)
	{
		if ((ptr->type == REDIN || ptr->type == REDOUT) && ptr->next->type == ARG)
		{
			ptr->str = ft_strjoin_char(ptr->str, ' ');
			ft_merge(ptr, ptr->next);
			sup = ptr->next;
			if (ptr->next->next)
				ptr->next = ptr->next->next;
			else if (!ptr->next->next)
				ptr->next = NULL;
			ft_free_token(sup);
		}
		if (ptr->next)
			ptr = ptr->next;
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_MERGE_RED" KRED " END " RESET KYEL "--------------------\n" RESET);
}
