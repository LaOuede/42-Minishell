#include "../../include/minishell.h"

void	ft_merge_allredin(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ALLREDIN" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;

	ptr1 = pars->line;
	ptr2 = pars->line;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != PIPE)
		{
			if (ptr1->type == REDIN && ptr2->type == REDIN)
			{
				ptr1->str = ft_strjoin_char(ptr1->str, ' ');
				ft_merge(ptr1, ptr2);
				ptr2->type = ERROR;
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	printf(KYEL "-------------------- FT_MERGE_ALLREDIN" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_allredout(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ALLREDOUT" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;

	ptr1 = pars->line;
	ptr2 = pars->line;
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
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	printf(KYEL "-------------------- FT_MERGE_ALLREDOUT" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_create_file(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CREATE_FILE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	char		*str;
	t_token		*ptr;
	int	i;

	i = 0;
	str = ">>";
	ptr = pars->line;
	g_jct->fds = ft_calloc(pars->nb_pipe, sizeof(int));
	while (ptr->next)
	{
		if (ptr->type == REDOUT && ptr->next->type == ARG)
		{
			printf("file name = %s\n", ptr->next->str);
			printf("ptr->str = %s\n", ptr->str);
			if (g_jct->fds[i])
				close(g_jct->fds[i]);
			if (ft_strncmp(ptr->str, str, 2) == 0)
			{
				g_jct->fds[i] = open(ptr->next->str, \
					O_RDWR | O_CREAT | O_APPEND, 0644);
				//pars->fl_redirout = 2;
			}
			else
			{
				g_jct->fds[i] = open(ptr->next->str, \
					O_RDWR | O_CREAT | O_TRUNC, 0644);
				//pars->fl_redirout = 1;
			}
			if (g_jct->fds[i] == -1)
				ft_error_parsing(ERR_OUTFILE, REBUILDER, 1, pars);
			printf("g_jct->fds[%d] : %d\n", i, g_jct->fds[i]);
			//printf("pars->fl_redirout : %d\n", pars->fl_redirout);
			// if (file)
			//  close(file);
		}
		else if (ptr->type == PIPE)
			i++;
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CREATE_FILE" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_open_file(t_token *node, t_pars *pars)
{
	printf(KYEL "-------------------- FT_OPEN_FILE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	char *str;

	str = "<<";
	if (node->type == REDIN)
	{
		printf("file name or delimiter = %s\n", node->next->str);
		if (ft_strncmp(node->str, str, 2) == 0)
			exec_hd(pars, node->next->str);
		else
			pars->file_in = open(node->next->str, O_RDONLY);
		if (pars->file_in == -1)
			ft_error_parsing(ERR_INFILE, REBUILDER, 1, pars);
		printf("pars->file_in = %d\n", pars->file_in);
		// if (file)
		//  close(file);
	}
	printf(KYEL "-------------------- FT_OPEN_FILE" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_red(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_RED" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	t_token	*sup;

	ptr = pars->line;
	sup = NULL;
	while (ptr->next)
	{
		if ((ptr->type == REDIN || ptr->type == REDOUT) && ptr->next->type == ARG)
		{
			ft_open_file(ptr, pars);
			//ft_create_file(ptr, pars);
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
	printf(KYEL "-------------------- FT_MERGE_RED" KRED " END " RESET KYEL "--------------------\n" RESET);
}
