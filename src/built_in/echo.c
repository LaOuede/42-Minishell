#include "../../include/minishell.h"

/* ECHO
Definition :
	echo command returns strings directly from a command or script.
Prototype :
	echo [ OPTION(S) ] [ STRING ]
Flag -n :
	Omit newline from the output.
*/

void	ft_print(char *str, int j)
{
	while (str[++j])
		write(1, &str[j], 1);
	return ;
}

bool	ft_flag(char *str, int *j)
{
	printf(KYEL "-------------------- FT_FLAG" KGRN " START " RESET KYEL "--------------------\n" RESET);

	if (str[(*j)] == '-')
	{
		while(str[(*j)++])
		{
			if (ft_iswhitespace(str[(*j)]) == 1)
				return (true);
			if (str[(*j)] != 'n')
				return (false);
		}
	}
	return (false);
}

void	ft_msh_echo(t_jct *jct, int i)
{
	printf(KYEL "-------------------- FT_MSH_ECHO" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int	j;

	j = 0;
	if (jct->tab[i][1])
	{
		if (ft_flag(jct->tab[i][1], &j) == true)
			ft_print(jct->tab[i][1], j);
		else
		{
			j = -1;
			ft_print(jct->tab[i][1], j);
			write(1, "\n", 1);
		}
	}
	printf(KYEL "-------------------- FT_MSH_ECHO" KRED " END " RESET KYEL "--------------------\n" RESET);
}
