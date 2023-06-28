#include "../../include/minishell.h"

int	ft_get_ac(char **cmd)
{
	int	j;

	j = 0;
	while(cmd[j])
	{
		printf("cmd[%d]: %s\n", j, cmd[j]);
		j++;
	}
	return (j);
}