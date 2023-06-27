#include "../../include/minishell.h"

/* UNSET
Definition :
	Use the unset commmand to undefine a variable including function in BASH.
Prototype :
	unset function_name
*/

char	**ft_unset(char **envp, char *cmd)
{
	char	**new_envp;
	int		i;
	int 	len;
	int		j;

	len = 0;
	while(envp[len])
		len++;
	new_envp = ft_calloc(sizeof(*new_envp), len + 1);
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
	int i;

	i = -1;
	while (cmd[++i])
	{
		printf("c = %c\n", cmd[i]);
		if ((!ft_isalpha(cmd[i]) && cmd[i] != '_') || ft_strchr(cmd, '='))
		{
			fprintf(stderr, "unset: %s not a valid identifier\n", cmd);
			return (false);
		}
	}
	free(cmd);
	return (true);
}

void	ft_msh_unset(t_ms *ms, char **cmd)
{
	printf(KYEL "-------------------- FT_MSH_UNSET" KGRN " START " RESET KYEL "--------------------\n" RESET);
	(void)ms;
	int i;

	i = 0;
	//valider si le unset existe dans l'env
	while (cmd[++i])
	{
		if (!ft_isvalid(cmd[i]))
		{
			if (ms->exec->cmd_nb == 1)
				ft_exit_free(ms, 1);
			else
			{
				ft_free_all(ms);
				return ;
			}
		}
		ms->exec->envp = ft_unset(ms->exec->envp, ft_strjoin(cmd[i], "="));
		ms->jct->envp = ms->exec->envp;
	}
	printf(KYEL "-------------------- FT_MSH_UNSET" KRED " END " RESET KYEL "--------------------\n" RESET);
}
