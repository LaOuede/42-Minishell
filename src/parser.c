#include "../include/minishell.h"

/* Store the nodes in a two-dimensionnal array */
void	ft_extract_points(t_jct *jct, t_pars *pars)
{
	int		row;
	int		column;
	t_token	*ptr;

	row = -1;
	column = -1;
	ptr = pars->line;
	while (++row < jct->cmd_nb || ptr)
	{
		while (++column < 4 || ptr)
		{
			if (column == ptr->tab_type)
				jct->tab[row][column] = *ft_strdup(ptr->str);
			else
				jct->tab[row][column] = (char)ft_calloc(1, sizeof(char));
			ptr = ptr->next;
		}
	}
	ft_clean_up(pars, 0);
}

/* Initializes the two-dimensioonnal array. */
void	ft_init_cmdtab(t_jct *jct)
{
	int	i;

	jct->tab = ft_calloc(jct->cmd_nb, sizeof(char *));
	if (!jct->tab)
		ft_clean_up_jct(jct, KYEL"-> Failed to init the command tab <-"KNRM);
	i = -1;
	while (++i < jct->cmd_nb)
	{
		jct->tab[i] = ft_calloc(4, sizeof(int));
		if (!jct->tab[i])
			ft_clean_up_jct(jct, KYEL"-> Failed to init the command tab <-"KNRM);
	}
}

void	ft_cmd_type(t_token **list)
{
	t_token	*ptr;

	if (!list)
		return ;
	ptr = *list;
	while (ptr)
	{
		if (ptr->type == -1)
			ptr->tab_type = 0;
		else if (ptr->type == 0)
			ptr->tab_type = 1;
		else if (ptr->type == 5 || ptr->type == 6)
			ptr->tab_type = 2;
		else if (ptr->type == 7 || ptr->type == 8)
			ptr->tab_type = 3;
		ptr = ptr->next;
	}
}

t_jct	*ft_init_jct(t_pars *pars)
{
	static t_jct	*jct;

	if (!jct)
	{
		jct = ft_calloc(1, sizeof(t_jct));
		jct->tab = NULL;
		jct->pipe_nb = pars->nb_pipe;
		jct->cmd_nb = pars->nb_pipe - 1;
	}
	return (jct);
}

void	ft_parser(t_pars *pars)
{
	t_jct	*jct;

	if (!pars)
		return ;
	jct = ft_init_jct(pars);
	ft_cmd_type(&pars->line);
	ft_parser_debugger(pars);
	ft_init_cmdtab(jct);
}
