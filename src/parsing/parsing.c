/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:42:32 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Initialization of the char ***tab.
*/
t_tab	*ft_init_tab(t_ms *ms, t_pars *pars)
{
	t_tab	*tab;

	tab = ft_calloc_msh(1, sizeof(t_tab), ms);
	tab->ptr = pars->line;
	tab->r = -1;
	tab->c = -1;
	return (tab);
}

/* Reset variables after a new node was created  */
void	ft_reset_node(t_pars *pars)
{
	pars->type = ARG;
	pars->fl_ws = 0;
	pars->d_quotes = 0;
	pars->s_quotes = 0;
}

void	ft_reset_pars(t_pars *pars)
{
	ft_free_lst(&pars->line);
	pars->line = NULL;
	pars->input = NULL;
	pars->strlen = 0;
	pars->nb_pipe = 1;
	pars->type = ARG;
	pars->d_quotes = 0;
	pars->s_quotes = 0;
	pars->c_brackets = 0;
	pars->fl_ws = 0;
	pars->hd = 0;
	pars->fl_red = false;
	pars->fl_pipe = false;
	pars->err_infile = false;
	pars->err_lexer = false;
	pars->err_builder = false;
	pars->err_filler = false;
	pars->err_parser = false;
}

/* Main parsing structure initialization */
t_pars	*ft_init_pars(t_ms *ms)
{
	t_pars	*pars;

	pars = ft_calloc_msh(1, sizeof(t_pars), ms);
	pars->line = NULL;
	pars->input = NULL;
	pars->envp = ms->envp;
	pars->path_var = ft_get_path(ms, pars->envp, 0);
	pars->strlen = 0;
	pars->nb_pipe = 1;
	pars->type = ARG;
	pars->d_quotes = 0;
	pars->s_quotes = 0;
	pars->c_brackets = 0;
	pars->hd = 0;
	pars->fl_ws = 0;
	pars->fl_red = false;
	pars->fl_pipe = false;
	pars->err_infile = false;
	pars->err_lexer = false;
	pars->err_builder = false;
	pars->err_filler = false;
	pars->err_parser = false;
	return (pars);
}

/*
Main function for parsing.
Calls Lexer, Builder and Parser one at a time if flag are "false".
- Lexer = Breaks input in token and put them in a linked-list.
- Builder = Open and Create files redirections.
			Assembles token together by type in the linked-list.
- Parser = Check for any invalid token and transforms
	linked-list in a char ***tab.
Produces a char *** array which is received by the executioner.
*/
void	ft_parsing(t_ms *ms)
{
	ft_lexer(ms);
	if (!ms->pars->line)
		ms->pars->err_lexer = true;
	if (ms->pars->line && ms->pars->err_lexer == false)
	{
		ft_builder(ms);
		if (ms->pars->err_builder == false)
			ft_filler(ms);
	}
	if (ms->pars->err_lexer == true || ms->pars->err_builder == true \
		|| ms->pars->err_filler == true)
		ms->jct->err_pars = true;
	ft_reset_pars(ms->pars);
}
