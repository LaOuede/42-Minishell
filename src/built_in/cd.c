#include "../../include/minishell.h"

/* CD
Definition :
	cd command is a built-in command in Bash that is used to
	change current working directory.
	The "absolute" path of a directory is its location relative to the root folder.
	The "relative" path is its location relative to the current directory.
	The slash character / is used to represent a subfolder
	The .. character is used to move to a parent folder.
Prototype :
	cd [directory]
*/

void	ft_update_oldpwd(t_ms *ms)
{
	char	*olddir[3];

	olddir[0] = "export";
	olddir[1] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	olddir[2] = NULL;
	ft_msh_export(ms, (char **)olddir);
	free(olddir[1]);
}

int	ft_isexist(t_ms *ms, char *home)
{
	int	i;
	int	j;
	int	ac;

	ac = ft_get_ac(ms->envp);
	i = 0;
	while (ms->envp[i] && ft_strncmp(ms->envp[i], home, 5) != 0)
		i++;
	j = i;
	if (++j > ac)
		return (-1);
	else
		return (i);
}

char	*ft_getenv(t_ms *ms, char *home)
{
	int		index;
	char	**path_var;
	char	*tmp;

	tmp = NULL;
	path_var = NULL;
	if (!ms->envp)
		return (NULL);
	index = ft_isexist(ms, home);
	if (index < 0)
		return (NULL);
	path_var = ft_split(ms->envp[index], '=');
	if (path_var[1])
	{
		tmp = ft_strdup(path_var[1]);
		ft_free_tab_char(path_var);
		return(tmp);
	}
	else
	{
		ft_free_tab_char(path_var);
		return (NULL);
	}
}

char *ft_get_dir(t_ms *ms, char **cmd)
{
	char *home;
	
	home = NULL;
	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
	{
		home = ft_getenv(ms, "HOME=");
		return (home);
	}
	else
		return (cmd[1]);
}

int	ft_do_chdir(t_ms *ms, char *cd)
{
	char	*newdir[3];

	if(chdir(cd) == -1)
		return(0);
	newdir[0] = "export";
	newdir[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	newdir[2] = NULL;
	ft_msh_export(ms, (char **)newdir);
	free(newdir[1]);
	return (1);
}

void	ft_msh_cd(t_ms *ms, char **cmd)
{
	int	ac;
	char *cd;
	
	if (!getcwd(NULL, 0))
	{
		perror("cd");
		return ;
	}
	ac = ft_get_ac(cmd);
	if (ac > 2)
	{
		ft_putstr_fd("Too many args - Usage: env [no opt/args]\n", 2);
		ms->flexit = 1;
		return ;
	}
	else
	{
		ft_update_oldpwd(ms);
		cd = ft_get_dir(ms, cmd);
		if(ft_do_chdir(ms, cd) < 1)
		{
			perror("Error! cd");
			return ;
		}
	}
}

