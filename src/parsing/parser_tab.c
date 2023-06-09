#include "../../include/minishell.h"

char	*ft_trim(char *str, char c)
{
	int		len;
	int		i;
	char	*s_trim;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && ft_strchr(&c, str[i]))
		i++;
	len = ft_strlen(str);
	s_trim = ft_substr(str, i, len - i + 1);
	ft_freenull(str);
	return (s_trim);
}

void	ft_trim_cmd(t_jct *jct)
{
	printf(KYEL "-------------------- FT_TRIM_CMD" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int		cmd;

	cmd = -1;
	while (++cmd < jct->cmd_nb)
	{
		jct->tab[cmd][0] = ft_trim(jct->tab[cmd][0], ' ');
		printf("CMD = %s\n", jct->tab[cmd][0]);
	}
	printf(KYEL "-------------------- FT_TRIM_CMD" KRED " END " RESET KYEL "--------------------\n" RESET);
}

/* Store the nodes in a two-dimensionnal array */
void	ft_fill_tab(t_jct *jct, t_pars *pars)
{
	printf(KYEL "-------------------- FT_FILL_TAB" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int		row;
	int		column;
	t_token	*ptr;

	row = -1;
	ptr = pars->line;
	//TODO J'ai 
	jct->file_out = dup(pars->file_out);	
	jct->file_in = dup(pars->file_in);
	close(pars->file_in);
	close(pars->file_out);
	printf("jct->file_out : %d\n", jct->file_out);
	printf("pars->file_out : %d\n", pars->file_out);
	printf("jct->file_in : %d\n", jct->file_in);
	printf("pars->file_in : %d\n", pars->file_in);
	printf("jct->cmd_nb = %d\n", jct->cmd_nb);
	printf("pars->nb_pipe = %d\n", pars->nb_pipe);
	while (++row < jct->cmd_nb && ptr)
	{
		column = -1;
		while (++column < 4)
		{
			printf("column = %d\n", column);
			printf("ptr->type = %d\n", ptr->type);
			if (ptr->type == 4 && column == 0)
				ptr = ptr->next;
			if (column == ptr->type)
			{
				jct->tab[row][column] = ft_strdup(ptr->str);
				printf("str = %s\n", jct->tab[row][column]);
				if (ptr->next)
					ptr = ptr->next;
			}
			else if (column != ptr->type)
			{
				if (ptr->type != 4)
					jct->tab[row][column] = NULL;
				else
				{
					while (column < 4)
						jct->tab[row][column++] = NULL;
				}
			}
		}
	}
	printf(KYEL "-------------------- FT_FILL_TAB" KRED " END " RESET KYEL "--------------------\n" RESET);
}

/* Initializes the two-dimensioonnal array. */
void	ft_init_cmdtab(t_jct *jct)
{
	int	i;

	jct->tab = ft_calloc(jct->cmd_nb + 1, sizeof(char **));
	if (!jct->tab)
	{
		ft_free_3tab(jct);
		return ;
	}
	i = -1;
	while (++i < jct->cmd_nb)
	{
		jct->tab[i] = ft_calloc(4, sizeof(char *));
		if (!jct->tab[i])
		{
			ft_free_3tab(jct);
			return ;
		}
	}
}
