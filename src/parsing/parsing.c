#include "../../include/minishell.h"

/*
Initialization of the char ***tab.
*/
t_tab	*ft_init_tab(t_pars *pars)
{
	t_tab	*tab;

	tab = ft_calloc(1, sizeof(t_tab));
	tab->ptr = pars->line;
	tab->r = -1;
	tab->c = -1;
	return (tab);
}

/* Reset variables after a new node was created  */
void	ft_reset_node(t_pars *pars)
{
	pars->type = ARG;
	pars->flag_whitespace = 0;
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
	pars->flag_whitespace = 0;
	pars->err_lexer = false;
	pars->err_rebuilder = false;
	pars->err_parser = false;
}

/* Main parsing structure initialization */
t_pars	*ft_init_pars(t_ms *ms)
{
	t_pars	*pars;

	pars = ft_calloc(1, sizeof(t_pars));
	pars->line = NULL;
	pars->input = NULL;
	pars->envp = ms->jct->envp;
	pars->path_var = ft_get_path(pars->envp, 0);
	pars->strlen = 0;
	pars->nb_pipe = 1;
	pars->type = ARG;
	pars->d_quotes = 0;
	pars->s_quotes = 0;
	pars->c_brackets = 0;
	pars->flag_whitespace = 0;
	pars->err_lexer = false;
	pars->err_rebuilder = false;
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
	printf(KYEL "-------------------- FT_PARSING" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	ft_lexer(ms);
	if (!ms->pars->line)
		ms->pars->err_lexer = true;
	DEBUG_lexer(ms->pars);
	if (ms->pars->line && ms->pars->err_lexer == false)
	{
		ft_builder(ms);
		DEBUG_builder(ms->pars);
		if (ms->pars->err_rebuilder == false)
			ft_parser(ms);
	}
	if (ms->pars->err_lexer == true || ms->pars->err_rebuilder == true \
			|| ms->pars->err_parser == true)
			ms->jct->err_pars = true;
		ft_reset_pars(ms->pars);
	if (DEBUG)
		printf(KYEL "-------------------- FT_PARSING" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}
