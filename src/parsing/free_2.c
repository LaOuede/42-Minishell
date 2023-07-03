/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:42:05 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_child(t_ms *ms)
{
	if (ms)
	{
		if (ms->pars)
			ft_free_pars(ms->pars);
		if (ms->exec)
			ft_free_exec(ms->exec);
		ms = ft_freenull(ms);
	}
}

void	ft_free_all(t_ms *ms)
{
	if (ms)
	{
		if (ms->jct)
			ft_free_jct(ms->jct);
		if (ms->pars)
			ft_free_pars(ms->pars);
		if (ms->exec)
			ft_free_exec(ms->exec);
		if (ms->hd)
			ft_free_pars(ms->hd);
		if (ms->envp)
			ft_free_tab_char(ms->envp);
		ms = ft_freenull(ms);
	}
}
