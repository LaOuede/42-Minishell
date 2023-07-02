#include "../../include/minishell.h"

void	ft_creation(t_ms *ms, t_token ptr, char *str, int *i)
{
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
}

void	ft_create_file(t_ms *ms)
{
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
}

void	ft_open_hd(t_ms *ms)
{
	char	*str;
	t_token	*ptr;

	str = "<<";
	ptr = ms->pars->line;
	while (ptr->next)
	{
		if (ptr->type == REDIN && ptr->next->type == ARG)
		{
			if (ms->jct->fd_hd)
				close(ms->jct->fd_hd);
			if (ft_strncmp(ptr->str, str, 2) == 0 && ptr->next->str[0] != 29)
				ft_exec_hd(ptr->next->str, ms);
		}
		ptr = ptr->next;
	}
}

void	ft_open_file(t_ms *ms)
{
	int		i;
	char	*str;
	t_token	*ptr;

	i = 0;
	str = "<";
	ptr = ms->pars->line;
	while (ptr->next)
	{
		if (ptr->type == REDIN && ptr->next->type == ARG)
		{
			if (ms->jct->fds_in[i])
				close(ms->jct->fds_in[i]);
			if (ft_strncmp(ptr->str, str, 2) == 0)
			{
				ms->jct->fds_in[i] = open(ptr->next->str, O_RDONLY);
				if (ms->jct->fds_in[i] == -1)
				{
					printf(ERR_INFILE);
					ms->pars->err_infile = true;
					break ;
				}
			}
		}
		else if (ptr->type == PIPE)
			i++;
		ptr = ptr->next;
	}
}

void	ft_merge_red(t_ms *ms)
{
	t_token	*ptr;
	t_token	*sup;

	ptr = ms->pars->line;
	sup = NULL;
	while (ptr->next)
	{
		if ((ptr->type == REDIN || ptr->type == REDOUT) \
			&& ptr->next->type == ARG)
		{
			ptr->str = ft_strjoin_char(ms, ptr->str, ' ');
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
}
