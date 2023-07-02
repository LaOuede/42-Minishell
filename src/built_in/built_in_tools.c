#include "../../include/minishell.h"

int	ft_get_ac(char **cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
		j++;
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
		if ((!ft_isalpha(cmd[0]) && cmd[0] != '_' && cmd[0] != '=') \
			|| !ft_isalnum(cmd[j]))
		{
			printf("c[%d]: %c not a valid identifier\n", j, cmd[j]);
			ms->flexit = EXIT_FAILURE;
			return (false);
		}
	}
	return (true);
}

char	*ft_trim_arg_util(char **var)
{
	int		i;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	tmp1 = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	while (var[++i])
	{
		tmp1 = ft_strtrim(var[i], " ");
		if (tmp3)
		{
			tmp2 = ft_strjoin(tmp3, "=");
			tmp3 = ft_freenull(tmp3);
		}
		else
			tmp2 = ft_strjoin(var[0], "=");
		tmp3 = ft_strjoin(tmp2, tmp1);
		tmp1 = ft_freenull(tmp1);
		tmp2 = ft_freenull(tmp2);
	}
	return (tmp3);
}

char	*ft_trim_arg(char *cmd)
{
	char	*tmp;
	char	**var;

	tmp = NULL;
	var = ft_split(cmd, '=');
	if (var[1])
	{
		tmp = ft_trim_arg_util(var);
		ft_free_tab_char(var);
		return (tmp);
	}
	ft_free_tab_char(var);
	return (ft_strdup(cmd));
}
