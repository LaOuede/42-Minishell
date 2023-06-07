#include "../include/minishell.h"

void	ft_merge_pipe(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_IN" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	t_token	*sup;
	char	*new_str;

	if (!pars->line)
		return ;
	ptr = pars->line;
	new_str = NULL;
	while (ptr->next)
	{
		printf("str = %s\n", ptr->str);
		printf("str next = %s\n", ptr->next->str);
		if (ptr->type == PIPE && ptr->next->type == PIPE)
		{
			new_str = ft_strjoin(ptr->str, ptr->next->str);
			ptr->str = ft_strdup(new_str);
			printf("new str = %s\n", ptr->str);
			ft_freenull(new_str);
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
	printf(KYEL "-------------------- FT_MERGE_IN" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_swap(t_pars *pars)
{
	printf(KYEL "-------------------- FT_SWAP" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;
	int		swap;
	char	*str;

	if (!pars->line)
		return ;
	ptr1 = pars->line;
	ptr2 = ptr1;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != 4)
		{
			if (ptr1->type > ptr2->type && ptr1->type != PIPE && ptr2->type != PIPE)
			{
				swap = ptr1->type;
				ptr1->type = ptr2->type;
				ptr2->type = swap;
				str = ptr1->str;
				ptr1->str = ptr2->str;
				ptr2->str = str;
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	printf(KYEL "-------------------- FT_SWAP" KRED " END " RESET KYEL "--------------------\n" RESET);
}

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

void	ft_find_arg(t_pars *pars)
{
	printf(KYEL "-------------------- FT_FIND_ARG" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	bool	flag;

	ptr = pars->line;
	flag = true;
	while (ptr)
	{
		printf("flag = %d\n", flag);
		printf("str = %s\n", ptr->str);
		printf("str->type before= %d\n", ptr->type);
		if (ptr->type == ARG && flag == true)
			flag = false;
		else if (ptr->type == ARG && flag == false)
			ptr->type = ERROR;
		if (ptr->type == PIPE)
			flag = true;
		printf("str->type after = %d\n", ptr->type);
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_FIND_ARG" KRED " END " RESET KYEL "--------------------\n" RESET);
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

void	ft_merge_allredin(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ALLREDIN" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;
	char	*new_str;
	char	*tmp;

	if (!pars->line)
		return ;
	ptr1 = pars->line;
	ptr2 = ptr1;
	new_str = NULL;
	tmp = NULL;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != 4)
		{
			if (ptr1->type == REDIN && ptr2->type == REDIN)
			{
				if (ptr1->str && !ptr2->str)
					new_str = ft_strdup(ptr1->str);
				else if (!ptr1->str && ptr2->str)
					new_str = ft_strdup(ptr2->str);
				else if (ptr1->str && ptr2->str)
				{
					ptr1->str = ft_strjoin_char(ptr1->str, ' ');
					new_str = ft_strjoin(ptr1->str, ptr2->str);
				}
				tmp = ptr1->str;
				ptr1->str = ft_strdup(new_str);
				ft_freenull(tmp);
				ft_freenull(new_str);
				printf("new_str = %s\n", new_str);
				printf("ptr->str = %s\n", ptr1->str);
				printf("ptr->next->str = %s\n", ptr2->str);
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	ft_freenull(new_str);
	printf(KYEL "-------------------- FT_MERGE_ALLREDIN" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_allredout(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ALLREDOUT" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;
	char	*new_str;
	char	*tmp;

	if (!pars->line)
		return ;
	ptr1 = pars->line;
	ptr2 = ptr1;
	new_str = NULL;
	tmp = NULL;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != 4)
		{
			if (ptr1->type == REDOUT && ptr2->type == REDOUT)
			{
				if (ptr1->str && !ptr2->str)
					new_str = ft_strdup(ptr1->str);
				else if (!ptr1->str && ptr2->str)
					new_str = ft_strdup(ptr2->str);
				else if (ptr1->str && ptr2->str)
				{
					ptr1->str = ft_strjoin_char(ptr1->str, ' ');
					new_str = ft_strjoin(ptr1->str, ptr2->str);
				}
				tmp = ptr1->str;
				ptr1->str = ft_strdup(new_str);
				ft_freenull(tmp);
				ft_freenull(new_str);
				printf("new_str = %s\n", new_str);
				printf("ptr->str = %s\n", ptr1->str);
				printf("ptr->next->str = %s\n", ptr2->str);
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	printf(KYEL "-------------------- FT_MERGE_ALLREDOUT" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_check_error_pipe(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_REDIR" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	int		len;

	if (!pars->line)
		return ;
	ptr = pars->line;
	while (ptr)
	{
		if (ptr->type == PIPE)
		{
			len = ft_strlen(ptr->str);
			if (len > 1)
				ft_error_parsing(ERR_TOKEN, REBUILDER, pars);
		}
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CHECK_REDIR" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_check_error_redir(t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_REDIR" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	int		len;

	if (!pars->line)
		return ;
	ptr = pars->line;
	while (ptr)
	{
		if (ptr->type == REDIN || ptr->type == REDOUT)
		{
			len = ft_strlen(ptr->str);
			if (len > 2)
				ft_error_parsing(ERR_TOKEN, REBUILDER, pars);
		}
		ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_CHECK_REDIR" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_out(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_OUT" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	t_token	*sup;
	char	*new_str;

	if (!pars->line)
		return ;
	ptr = pars->line;
	new_str = NULL;
	while (ptr->next)
	{
		printf("str = %s\n", ptr->str);
		printf("str next = %s\n", ptr->next->str);
		if (ptr->type == REDOUT && ptr->next->type == REDOUT)
		{
			new_str = ft_strjoin(ptr->str, ptr->next->str);
			ptr->str = ft_strdup(new_str);
			printf("new str = %s\n", ptr->str);
			ft_freenull(new_str);
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
	printf(KYEL "-------------------- FT_MERGE_OUT" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_in(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_IN" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	t_token	*sup;
	char	*new_str;

	if (!pars->line)
		return ;
	ptr = pars->line;
	new_str = NULL;
	while (ptr->next)
	{
		printf("str = %s\n", ptr->str);
		printf("str next = %s\n", ptr->next->str);
		if (ptr->type == REDIN && ptr->next->type == REDIN)
		{
			new_str = ft_strjoin(ptr->str, ptr->next->str);
			ptr->str = ft_strdup(new_str);
			printf("new str = %s\n", ptr->str);
			ft_freenull(new_str);
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
	printf(KYEL "-------------------- FT_MERGE_IN" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_create_file(t_token *node, t_pars *pars)
{
	printf(KYEL "-------------------- FT_CREATE_FILE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int	file;

	if (node->type == REDOUT)
	{
		printf("file name = %s\n", node->next->str);
		file = open(node->next->str, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (!file)
			ft_error_parsing(ERR_OUTFILE, REBUILDER, pars);
		if (file)
			close(file);
	}
	printf(KYEL "-------------------- FT_CREATE_FILE" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_open_file(t_token *node, t_pars *pars)
{
	printf(KYEL "-------------------- FT_OPEN_FILE" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int	file;

	if (node->type == REDIN)
	{
		printf("file name = %s\n", node->next->str);
		file = open(node->next->str, O_RDONLY);
		if (file == -1)
			ft_error_parsing(ERR_INFILE, REBUILDER, pars);
		printf("file = %d\n", file);
		if (file)
			close(file);
	}
	printf(KYEL "-------------------- FT_OPEN_FILE" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_red(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_RED" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr;
	t_token	*sup;
	char	*new_str;
	char	*tmp;

	if (!pars->line)
		return ;
	ptr = pars->line;
	new_str = NULL;
	tmp = NULL;
/* 	printf("str = %s\n", ptr->str);
	printf("str next = %s\n", ptr->next->str);
	printf("ptr->type = %d\n", ptr->type); */
	while (ptr->next)
	{
		if ((ptr->type == REDIN || ptr->type == REDOUT) && ptr->next->type == ARG)
		{
			ft_open_file(ptr, pars);
			ft_create_file(ptr, pars);
			if (ptr->str && !ptr->next->str)
				new_str = ft_strdup(ptr->str);
			else if (!ptr->str && ptr->next->str)
				new_str = ft_strdup(ptr->next->str);
			else if (ptr->str && ptr->next->str)
			{
				ptr->str = ft_strjoin_char(ptr->str, ' ');
				new_str = ft_strjoin(ptr->str, ptr->next->str);
			}
			tmp = ptr->str;
			ptr->str = ft_strdup(new_str);
			ft_freenull(tmp);
			ft_freenull(new_str);
/* 			printf("new_str = %s\n", new_str);
			printf("ptr->str = %s\n", ptr->str);
			printf("ptr->next->str = %s\n", ptr->next->str); */
			sup = ptr->next;
			if (ptr->next->next)
			{
				printf("test1\n");
				ptr->next = ptr->next->next;
			}
			else if (!ptr->next->next)
			{
				printf("test2\n");
				ptr->next = NULL;
			}
			ft_free_token(sup);
		}
		if (ptr->next)
			ptr = ptr->next;
	}
	printf(KYEL "-------------------- FT_MERGE_RED" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_merge_arg(t_pars *pars)
{
	printf(KYEL "-------------------- FT_MERGE_ARG" KGRN " START " RESET KYEL "--------------------\n" RESET);
	t_token	*ptr1;
	t_token	*ptr2;
	char	*new_str;
	char	*tmp;

	if (!pars->line)
		return ;
	ptr1 = pars->line;
	ptr2 = pars->line;
	new_str = NULL;
	tmp = NULL;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 && ptr2->type != 4)
		{
			if (ptr1->type == ARG && ptr2->type == ARG)
			{
				if (ptr1->str && !ptr2->str)
					new_str = ft_strdup(ptr1->str);
				else if (!ptr1->str && ptr2->str)
					new_str = ft_strdup(ptr2->str);
				else if (ptr1->str && ptr2->str)
				{
					if (ptr2->ws == 1)
						ptr1->str = ft_strjoin_char(ptr1->str, ' ');
					new_str = ft_strjoin(ptr1->str, ptr2->str);
				}
				tmp = ptr1->str;
				ptr1->str = ft_strdup(new_str);
				ft_freenull(tmp);
				ft_freenull(new_str);
				printf("ptr->str = %s\n", ptr1->str);
				printf("ptr->next->str = %s\n", ptr2->str);
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	printf(KYEL "-------------------- FT_MERGE_ARG" KRED " END " RESET KYEL "--------------------\n" RESET);
}

void	ft_builder(t_pars *pars)
{
	printf(KYEL "-------------------- FT_REBUILDER" KGRN " START " RESET KYEL "--------------------\n" RESET);
	ft_merge_pipe(pars);
	ft_check_error_pipe(pars);
	ft_merge_in(pars);
	ft_merge_out(pars);
	ft_check_error_redir(pars);
	ft_merge_red(pars);
	ft_merge_allredin(pars);
	ft_merge_allredout(pars);
	ft_find_cmd(pars);
	ft_merge_arg(pars);
	ft_find_arg(pars);
	ft_find_redin(pars);
	ft_find_redout(pars);
	ft_clean_list(&pars->line);
	ft_swap(pars);
	printf(KYEL "-------------------- FT_REBUILDER" KRED " END " RESET KYEL "--------------------\n" RESET);
}
