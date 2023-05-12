#include "../include/minishell.h"

char	*ft_cmd_path(t_exec *exec, char *cmds)
{
	char	*path;
	int		i;

	if (access(cmds, X_OK | F_OK) == 0)
		return (ft_strdup(cmds));
	path = ft_strjoin("./", cmds);
	if (access(path, X_OK | F_OK) == 0)
		return (path);
	free(path);
	i = -1;
	while (exec->cmd_paths[++i])
	{
		path = ft_strjoin(exec->cmd_paths[i], cmds);
		if (access(path, X_OK | F_OK) == 0)
			return (path);
		free(path);
	}
	ft_err("Error ! Can't find path to program", exec);
	path = NULL;
	return (path);
}

void	ft_exec(t_exec *exec)
{
	char	*path;
	char	**cmds;
	int		i;

	cmds = ft_split(exec->av[exec->index], ' '); // TODO note : surement pas utile car ce sera dans des tokens deja separés
	path = ft_cmd_path(exec, cmds[0]); // TODO note : 
	if (!path)
		free(path);
	else if (execve(path, cmds, exec->envp) < 0)
		ft_err("Error ! Something went wrong while executing: ", exec);
	i = 0;
	while (exec->cmd_paths[i])
		free(exec->cmd_paths[i++]);
	free(exec->cmd_paths[i++]);
	free(exec->cmd_paths);
	exec->cmd_paths = NULL;
}