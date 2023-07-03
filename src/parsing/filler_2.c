/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:41:57 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_fill_null_error(t_ms *ms, t_tab *tab)
{
	if (tab->ptr->type == ACCESS_ERR && tab->c == 0)
	{
		ms->jct->tab[tab->r][tab->c] = ft_strdup(tab->ptr->str);
		if (tab->ptr->next)
			tab->ptr = tab->ptr->next;
	}
	else if (tab->ptr->type != PIPE)
		ms->jct->tab[tab->r][tab->c] = NULL;
	else
		while (tab->c < 3)
			ms->jct->tab[tab->r][tab->c++] = NULL;
}

/*
Fill the char ***array with nodes of the linked-list.
***FROM***
Input : cat supp.txt >outfile | cat -e | ls < infile | echo -n Minihell
***TO***
--------------------------------------------------------------
-                           TAB                              -
--------------------------------------------------------------
[0][0] = cat supp.txt
[0][1] = (null)
[0][2] = > outfile
--------------------------------------------------------------
[1][0] = cat -e
[1][1] = (null)
[1][2] = (null)
--------------------------------------------------------------
[2][0] = ls
[2][1] = < infile
[2][2] = (null)
--------------------------------------------------------------
[3][0] = cat -n Minihell
[3][1] = (null)
[3][2] = (null)
--------------------------------------------------------------
*/
void	ft_fill_tab(t_ms *ms, t_tab *tab)
{
	while (++tab->r < ms->jct->cmd_nb && tab->ptr)
	{
		tab->c = -1;
		while (++tab->c < 3)
		{
			if (tab->ptr->type == PIPE && tab->c == 0)
				tab->ptr = tab->ptr->next;
			if (tab->c == tab->ptr->type)
			{
				ms->jct->tab[tab->r][tab->c] = ft_strdup(tab->ptr->str);
				if (tab->ptr->next)
					tab->ptr = tab->ptr->next;
			}
			else if (tab->c != tab->ptr->type)
				ft_fill_null_error(ms, tab);
		}
	}
}

/* Allocate memory for the char ***array. */
void	ft_init_cmdtab(t_ms *ms)
{
	int	i;

	ms->jct->tab = ft_calloc_msh(ms->jct->cmd_nb + 1, sizeof(char **), ms);
	if (!ms->jct->tab)
	{
		ft_free_3tab(ms->jct);
		return ;
	}
	i = -1;
	while (++i < ms->jct->cmd_nb)
	{
		ms->jct->tab[i] = ft_calloc_msh(3, sizeof(char *), ms);
		if (!ms->jct->tab[i])
		{
			ft_free_3tab(ms->jct);
			return ;
		}
	}
}
