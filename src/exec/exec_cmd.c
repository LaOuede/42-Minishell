/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:40:26 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_cmd_path(t_exec *exec, char *cmds)
{
	char	*path;
	int		i;

	if (access(cmds, F_OK | X_OK) == 0)
		return (ft_strdup(cmds));
	path = ft_strjoin("./", cmds);
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	if (path)
		path = ft_freenull(path);
	i = -1;
	while (exec->path_var[++i])
	{
		path = ft_strjoin(exec->path_var[i], cmds);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		if (path)
			path = ft_freenull(path);
	}
	path = NULL;
	return (path);
}

void	ft_run_cmd(t_ms *ms, int r)
{
	char	*path;
	char	**opt;
	char	**envp;

	opt = ft_split(ms->jct->tab[r][0], 29);
	path = ft_cmd_path(ms->exec, opt[0]);
	envp = ms->envp;
	if (!path)
	{
		ft_free_tab_char(opt);
		ft_free_all(ms);
		exit(127);
	}
	if (execve(path, opt, envp) < 0)
	{
		perror("Error! Something went wrong while executing");
		free(path);
		ft_free_tab_char(opt);
		ft_free_all(ms);
		exit(127);
	}
}
