/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_redirection_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:41:27 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_do_check(t_ms *ms, t_token *node)
{
	int		len;

	len = ft_strlen(node->str);
	if (ms->pars->fl_red == false && (len > 2 \
		|| (node->next && node->next->type == REDIN) \
		|| (node->next && node->next->type == REDOUT)))
	{
		ms->pars->fl_red = true;
		ft_error_parsing(ERR_TOKEN, REBUILDER, 258, ms);
	}
	else if (ms->pars->fl_red == 0 \
		&& (!node->next || node->next->str[0] == 29))
	{
		ms->pars->fl_red = true;
		ft_error_parsing(ERR_TOKEN, REBUILDER, 258, ms);
	}
}

void	ft_check_error_redir(t_ms *ms)
{
	t_token	*ptr;

	if (!ms->pars->line)
		return ;
	ptr = ms->pars->line;
	while (ptr)
	{
		if (ptr->type == REDIN || ptr->type == REDOUT)
			ft_do_check(ms, ptr);
		ptr = ptr->next;
	}
}

void	ft_merge_angle_brackets_out(t_pars *pars)
{
	t_token	*ptr;
	t_token	*sup;

	ptr = pars->line;
	while (ptr->next)
	{
		if (ptr->next->ws == 0 && ptr->type == REDOUT \
			&& ptr->next->type == REDOUT)
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
}

void	ft_merge_angle_brackets_in(t_pars *pars)
{
	t_token	*ptr;
	t_token	*sup;

	ptr = pars->line;
	while (ptr->next)
	{
		if (ptr->next->ws == 0 && ptr->type == REDIN \
			&& ptr->next->type == REDIN)
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
