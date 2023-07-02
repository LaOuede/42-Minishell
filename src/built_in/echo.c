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
	int	i;

	i = 0;
	if (!str)
		return (false);
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
	while (*i <= arg)
	{
		if (ft_flag(ms, cmd[*i]) == true)
			(*i)++;
		else
			break ;
	}
	return (*i);
}

void	ft_msh_echo(t_ms *ms, char **cmd)
{
	int	i;
	int	nb;

	i = 1;
	nb = ft_get_ac(cmd) - 1;
	if (cmd)
	{
		if (nb == 1)
			if (ft_flag(ms, cmd[1]) == true)
				return ;
		i = ft_check_flag(ms, &i, nb, cmd);
		ft_handle_flag(ms, &i, nb, cmd);
	}
}
