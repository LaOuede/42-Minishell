#include "../../include/minishell.h"

int	ft_get_ac(char **cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (DEBUG)
			printf("cmd[%d]: %s\n", j, cmd[j]);
		j++;
	}
	return (j);
}

bool	ft_1st_part_valid(t_ms *ms, char *cmd)
{
	int	j;

	j = -1;
	while (cmd[++j])
	{
		while (cmd[j] == '_')
			j++;
		if (cmd[j] == '$' || cmd[j] == '?' || cmd[j] == '_')
			j++;
		if ((!ft_isalpha(cmd[0]) && cmd[0] != '_' && cmd[0] != '=') 
			|| !ft_isalnum(cmd[j]))
		{
			printf("c[%d]: %c not a valid identifier\n", j, cmd[j]);
			ft_freenull(cmd);
			ms->flexit = EXIT_FAILURE;
			return (false);
		}
	}
	return(true);
}
