#include "../../include/minishell.h"

/* ECHO
Definition :
	echo command returns strings directly from a command or script.
Prototype :
	echo [ OPTION(S) ] [ STRING ]
Flag -n :
	Omit newline from the output.
*/

bool	ft_flag(char *str)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_FLAG" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int	i;

	i = 0;
	if (str[(i)] == '-')
	{
		while (str[++i])
		{
			if (DEBUG)
				printf("char = %c\n", str[i]);
			if (str[i] != 'n')
				return (false);
		}
		return (true);
	}
	return (false);
}

void	ft_msh_echo(t_ms *ms, char **cmd)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_MSH_ECHO" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int	i;

	i = 1;
	if (cmd[1])
	{
		if (DEBUG)
			printf("flag = %d\n", ft_flag(cmd[1]));
		if (ft_flag(cmd[1]) == true)
		{
			while (cmd[++i])
			{
				if (cmd[i + 1])
					printf("%s ", cmd[i]);
				else
					printf("%s", cmd[i]);
			}
		}
		else
		{
			i = 0;
			while (cmd[++i])
			{
				if (cmd[i + 1])
					printf("%s ", cmd[i]);
				else
					printf("%s", cmd[i]);
			}
			printf("\n");
			ms->flexit = 0;
		}
	}
	if (!cmd[1])
		write(1, "\n", 1);
	else if (i < 2 && ms->jct->flag_err_var == true)
		write(1, "\n", 1);
	if (DEBUG)
		printf(KYEL "-------------------- FT_MSH_ECHO" KRED " END " RESET KYEL "--------------------\n" RESET);
}
