#include "../../include/minishell.h"

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
	pars->input = NULL;
	pars->line = NULL;
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

t_pars	*ft_init_pars(char **envp)
{
	static t_pars	*pars;

	if (!pars)
	{
		pars = ft_calloc(1, sizeof(t_pars));
		pars->input = NULL;
		pars->line = NULL;
		pars->envp = envp;
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
	return (pars);
}

/*
Main function for parsing. Calls Lexer and Parser
and then returns a 2D arry to the executioner
*/
void	ft_parsing(t_pars *pars, t_jct *jct)
{
	printf(KYEL "-------------------- FT_PARSING" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);

	if (!*pars->input)
		return ;
	ft_lexer(pars);
	DEBUG_lexer(pars);
	if (pars->line && pars->err_lexer == false)
	{
		ft_builder(pars);
		DEBUG_build(pars);
		if (pars->err_rebuilder == false)
			ft_parser(pars, jct);
	}
	if (pars->err_lexer == true || pars->err_rebuilder == true || pars->err_parser == true)
		jct->err_pars = true;
	printf("err_lexer = %d\n", pars->err_lexer);
	printf("err_rebuilder = %d\n", pars->err_rebuilder);
	printf("err_parser = %d\n", pars->err_parser);
	printf("err_pars = %d\n", jct->err_pars);
	ft_reset_pars(pars);
	printf(KYEL "-------------------- FT_PARSING" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}

/* TODO
1) DONE - No need to handle curly_brackets and parenthesis_brackets you fool!! 
So need to suppress functions
2) DONE - Also need to deal better with $ expansion. watch out for $ and $$...
   DONE - Need to deal with ${}
3) DONE - Check if whitespace flag is working. If not, handle it! ==> I think it's ok
4) DONE - Deal with double quotes and only after that deal with $ inside
5) DONE - Cleaning up the code a little bit (Need to redo this one!)
7) DONE - Re-construct the arguments (seems ok so far)
8) DONE - Clean up the linked-list (Remove empty node added)
9) DONE - Linked-list divided in cmd (CMD - ARG - REDIN - REDOUT)
10) DONE - Transfer linked-list into 2D table
11) DONE - Parse commands & Shoot error message when a parsing error is found

12) DONE (for now) - Handle memory wise girl !!
13) Check everything to make a list of what's missing.
14) Clean the code!

check : mem leaks with $expand quotes
*/