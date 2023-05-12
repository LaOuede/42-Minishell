#include "../include/minishell.h"

void	ft_err(char *msg, t_exec *exec)
{
	ft_free_exec(exec);
	perror(msg);
	exit(1);
}

void	ft_free_exec(t_exec *exec)
{
	int	i;

	if (exec)
	{
		i = 0;
		if (exec->cmd_paths)
		{
			while (exec->cmd_paths[i])
				free(exec->cmd_paths[i++]);
			free(exec->cmd_paths);
			exec->cmd_paths = NULL;
		}
		i = 0;
		if (exec->pipes)
		{
			while (i < exec->pipes_nb)
				free(exec->pipes[i++]);
			free(exec->pipes);
			exec->pipes = NULL;
		}
		if (exec->pids)
			free(exec->pids);
		free(exec);
	}
}

int	ft_cmd_paths_qty(char **cmd_paths)
{
	int	i;

	i = 0;
	while (cmd_paths[i])
		i++;
	return (i);
}

char	**ft_get_path(char **envp, int i)
{
	char	**cmd_paths;
	char	**new_cmd_paths;

	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
	{
		new_cmd_paths = ft_calloc(1, sizeof(char *));
		new_cmd_paths[0] = ft_calloc(1, sizeof(char));
		return (new_cmd_paths);
	}
	cmd_paths = ft_split(&envp[i][5], ':');
	if (!cmd_paths)
		return (NULL);
	new_cmd_paths = ft_calloc(ft_cmd_paths_qty(cmd_paths) + 1, sizeof(char *));
	if (!new_cmd_paths)
		return (NULL);
	i = -1;
	while (cmd_paths[++i])
	{
		new_cmd_paths[i] = ft_strjoin(cmd_paths[i], "/");
		free(cmd_paths[i]);
	}
	free(cmd_paths);
	return (new_cmd_paths);
}

t_exec	*ft_init_exec(int ac, char **av, char **envp)
{
	static t_exec	*exec;

	(void)ac;
	if (!exec)
	{
		exec = ft_calloc(1, sizeof(t_exec));
		exec->av = av;
		exec->envp = envp;
		exec->cmd_paths = ft_get_path(exec->envp, 0);
		exec->pipes = NULL;
		exec->index = 0;
		// exec->output = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		// exec->input = open(exec->av[1], O_RDONLY);
		// if (exec->output == -1)
		// 	ft_err("Error ! Couldn't create the output file", exec);
	}

	return(exec);
}