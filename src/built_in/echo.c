#include "../../include/minishell.h"

/* ECHO
Definition :
	echo command returns strings directly from a command or script.
Prototype :
	echo [ OPTION(S) ] [ STRING ]
Flag -n :
	Omit newline from the output.
*/
void	ft_handle_flag(t_ms *ms, int *i, int arg, char **cmd)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_HANDLE_FLAG" KGRN " START " RESET KYEL "--------------------\n" RESET);
	if (ms->jct->echo == true)
	{
		while (*i <= arg)
		{
			if (*i < arg)
				printf("%s ", cmd[*i]);
			else if (*i == arg)
				printf("%s", cmd[*i]);
			(*i)++;
		}
	}
	else
	{
		*i = 0;
		while (++(*i) <= arg)
		{
			if (*i < arg)
				printf("%s ", cmd[*i]);
			else if (*i == arg)
				printf("%s", cmd[*i]);
		}
		printf("\n");
	}
}

bool	ft_flag(t_ms *ms, char *str)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_FLAG" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (DEBUG)
		printf("str = %s\n", str);
	while (str[i])
	{
		if (str[i] == '-' && str[i + 1] == 'n')
		{
			i++;
			while (str[i] == 'n')
				i++;
			if (str[i] == '\0')
			{
				ms->jct->echo = true;
				return (true);
			}
			else
				return (false);
		}
		else
				return (false);
	}
	return (false);
}

int	ft_check_flag(t_ms *ms, int *i, int arg, char **cmd)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_CHECK_FLAG" KGRN " START " RESET KYEL "--------------------\n" RESET);
	while (*i <= arg)
	{
		if (DEBUG)
			printf("flag = %d\n", ft_flag(ms, cmd[*i]));
		if (ft_flag(ms, cmd[*i]) == true)
			(*i)++;
		else
			break ;
	}
	return (*i);
}

void	ft_msh_echo(t_ms *ms, char **cmd)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_MSH_ECHO" KGRN " START " RESET KYEL "--------------------\n" RESET);
	int	i;
	int	nb;

	i = 1;
	nb = ft_get_ac(cmd) - 1;
	if (DEBUG)
		printf("arg nd = %d\n", nb);
	if (cmd)
	{
		if (nb == 1)
			if (ft_flag(ms, cmd[1]) == true)
				return ;
		i = ft_check_flag(ms, &i, nb, cmd);
		ft_handle_flag(ms, &i, nb, cmd);
	}
	if (DEBUG)
		printf(KYEL "-------------------- FT_MSH_ECHO" KRED " END " RESET KYEL "--------------------\n" RESET);
}
