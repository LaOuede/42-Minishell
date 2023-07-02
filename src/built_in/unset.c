#include "../../include/minishell.h"

/* UNSET
Definition :
	Use the unset commmand to undefine a variable including function in BASH.
Prototype :
	unset function_name
*/

char	**ft_unset(t_ms *ms, char **envp, char *cmd)
{
	int		i;
	int		j;
	int 	len;
	char	**new_envp;

	len = 0;
	while(envp[len])
		len++;
	new_envp = ft_calloc_msh(len + 1, sizeof(*new_envp), ms);
	i = 0;
	j = 0;
	while(envp[i])
	{
		if (!ft_strnstr(envp[i], cmd, ft_strlen(cmd) + 1))
			new_envp[j++] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[j] = NULL;
	ft_free_tab_char(envp);
	free(cmd);
	return (new_envp);
}

bool	ft_isvalid(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		while (cmd[i] == '_')
			i++;
		if (cmd[i] == '$' || cmd[i] == '?')
			i++;
		if ((!ft_isalpha(cmd[0]) && cmd[0] != '_' && cmd[0] != '=') 
			|| !ft_isalnum(cmd[i]))
		{
			printf("unset: %s not a valid identifier\n", cmd);
			return (false);
		}
		i++;
	}
	return (true);
}

void	ft_msh_unset(t_ms *ms, char **cmd)
{
	int i;

	i = 0;
	(void)ms;
	while (cmd[++i])
	{
		if (ft_isvalid(cmd[i]))
			ms->envp = ft_unset(ms, ms->envp, ft_strjoin(cmd[i], "="));
		else
		{
			ms->flexit = EXIT_FAILURE;
			return ;
		}
	}
}
