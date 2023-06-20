#include "../../include/minishell.h"

/*
Initialization of the char ***tab.
*/
t_tab	*ft_init_tab(t_pars *pars)
{
	t_tab	*tab;

	tab = ft_calloc(1, sizeof(t_tab));
	tab->ptr = pars->line;
	tab->row = -1;
	tab->column = -1;
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

/* Reset variables after ending parsing and waiting for next input */
void	ft_reset_pars(t_pars *pars)
{
	ft_free_lst(&pars->line);
	pars->line = NULL;
	pars->input = NULL;
	pars->strlen = 0;
	pars->nb_pipe = 1;
	pars->type = ARG;
	pars->s_quotes = 0;
	pars->d_quotes = 0;
	pars->c_brackets = 0;
	pars->flag_whitespace = 0;
	pars->err_lexer = false;
	pars->err_rebuilder = false;
	pars->err_parser = false;
	//TODO do we still need those 3 variables ?
	pars->file_in = -1;
	pars->file_out = -1;
	pars->fl_redirout = 0;
}

/* Main parsing structure initialization */
t_pars	*ft_init_pars(char **envp, t_jct *jct)
{
	t_pars	*pars;

	pars = NULL;
	if (!pars)
	{
		pars = ft_calloc(1, sizeof(t_pars));
		pars->jct = jct;
		pars->line = NULL;
		pars->input = NULL;
		pars->envp = envp;
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
		//TODO do we still need those 3 variables ?
		//TODO check if it needs to be -1 or 0 (may trigger an error if -1)
		pars->file_in = -1;
		pars->file_out = -1;
		pars->fl_redirout = 0;
	}
	return (pars);
}

/*
Main function for parsing.
Calls Lexer, Builder and Parser one at a time if flag are "false".
- Lexer = Breaks input in token and put them in a linked-list.
- Builder = Open and Create files redirections. Assembles token together by type in the linked-list.
- Parser = Check for any invalid token and transforms linked-list in a char ***tab.
Produces a char *** array which is received by the executioner.
*/
void	ft_parsing(t_pars *pars)
{
	printf(KYEL "-------------------- FT_PARSING" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	ft_lexer(pars);
	if (!pars->line)
		pars->err_lexer = true;
	DEBUG_lexer(pars);
	if (pars->line && pars->err_lexer == false)
	{
		ft_builder(pars);
		DEBUG_builder(pars);
		if (pars->err_rebuilder == false)
			ft_parser(pars);
	}
	if (pars->err_lexer == true || pars->err_rebuilder == true \
			|| pars->err_parser == true)
			pars->jct->err_pars = true;
	//ft_reset_pars(pars);
	printf(KYEL "-------------------- FT_PARSING" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}
