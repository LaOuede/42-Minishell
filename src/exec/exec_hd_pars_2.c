/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hd_pars_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:40:47 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_hd(t_pars *hd, int fd_hd)
{
	t_token	*tmp;

	tmp = hd->line;
	while (tmp)
	{
		ft_putendl_fd(tmp->str, fd_hd);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);
}

void	ft_merge_hd(t_pars *hd)
{
	t_token	*ptr1;
	t_token	*ptr2;

	if (!hd->line)
		return ;
	ptr1 = hd->line;
	while (ptr1->next)
	{
		ptr2 = ptr1->next;
		while (ptr2)
		{
			if (ptr1->hd == ptr2->hd)
			{
				ft_merge(ptr1, ptr2);
				ptr2->type = ERROR;
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}

void	ft_envvar_token_hd(int *i, char *str, t_ms *ms)
{
	char	*tmp;

	tmp = NULL;
	while (ft_isenvvarchar(str[++(*i)]))
		tmp = ft_stock_char(ms, tmp, str[(*i)]);
	if (!tmp)
	{
		tmp = ft_stock_char(ms, tmp, '$');
		ft_add_token_bottom(&ms->hd->line, ft_create_node(ms, tmp, ms->hd));
	}
	else
	{
		tmp = ft_stock_char(ms, tmp, '=');
		tmp = ft_find_envvar(tmp, ms);
		if (tmp)
			ft_add_token_bottom(&ms->hd->line, ft_create_node(ms, tmp, ms->hd));
	}
	tmp = ft_freenull(tmp);
}
