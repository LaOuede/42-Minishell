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

void	ft_update(t_ms *ms, char *pwd)
{
	char	*dir[3];

	dir[0] = "export";
	dir[1] = ft_strjoin(pwd, getcwd(NULL, 0));
	dir[2] = NULL;
	printf("dir[1]: %s\n", dir[1]);
	ft_msh_export(ms, (char **)dir);
	ft_free_tab_char(dir);
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
	if (++j > ac && ft_strncmp(ms->envp[i], home, 5) != 0)
		return (-1);
	else
		return (i);
}

char	*ft_getenv(t_ms *ms, char *home)
{
	int		index;
	char	**path_var;
	char	*tmp;

	printf("-- ft_gentenv starts\n");
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
		printf("if(path_var)\npath_var = %s\n", path_var[1]);
		printf("ms->envp[%d] = %s\n", index, path_var[1]);
		ft_free_tab_char(path_var);
		return(tmp);
	}
	else
	{
		ft_free_tab_char(path_var);
		return (NULL);
	}
	printf("-- ft_gentenv ends\n");
}

char *ft_get_dir(t_ms *ms, char **cmd)
{
	char *home;
	
	home = NULL;
	if (cmd[1])
		return (cmd[1]);
	else
	{
		home = ft_getenv(ms, "HOME=");
		return (home);
	}
}

int	ft_do_chdir(t_ms *ms, char *cd)
{
	if(chdir(cd) == -1)
		return(0);
	ft_update(ms, "PWD=");
	return (1);
}

void	ft_msh_cd(t_ms *ms, char **cmd)
{
	// if (DEBUG)
		printf(KYEL "-------------------- FT_MSH_CD" KGRN " START " RT KYEL "--------------------\n" RT);
	int	ac;
	char *cd;
	
	ac = ft_get_ac(cmd);
	printf("ac: %d\n", ac);
	if (ac > 2)
	{
		ft_putstr_fd("Too many args - Usage: env [no opt/args]\n", 2);
		ms->flexit = 1;
		return ;
	}
	else
	{
		ft_update(ms, "OLDPWD=");
		cd = ft_get_dir(ms, cmd);
		if(ft_do_chdir(ms, cd) < 1)
		{
			perror("Error! cd");
			return ;
		}
	}
	// if (DEBUG)
		printf(KYEL "-------------------- FT_MSH_ECHO" KRED " END " RT KYEL "--------------------\n" RT);
}

	// if (ac < 3 && chdir(cmd[1]) != 0)
	// {
	// 	ft_export_oldpwd(ms);
	// 	perror("Error! cd");
	// 	ms->flexit = 1;
	// 	return ;
	// }
// void	ft_msh_cd(t_ms *ms, char **cmd)
// {
// 	// if (DEBUG)
// 		printf(KYEL "-------------------- FT_MSH_CD" KGRN " START " RT KYEL "--------------------\n" RT);
// 	int	ac;
// 	char *home;
	
// 	home = ft_getenv(ms, "HOME=");
// 	ac = ft_get_ac(cmd);
// 	printf("ac: %d\n", ac);
// 	if (ac < 2 || ft_strcmp(cmd[1], "~") == 0)
// 	{
// 		if(chdir(home) != 0)
// 		{
// 			perror("Error! chdir");
// 			ms->flexit = 1;
// 		}
// 	}
// 	else if (ac < 3 && chdir(cmd[1]) != 0)
// 	{
// 		ft_export_oldpwd(ms);
// 		perror("Error! chdir");
// 		ms->flexit = 1;
// 		return ;
// 	}
// 	else if(ac >= 3)
// 	{
// 		ft_putstr_fd("Too many args - Usage: env [no opt/args]\n", 2);
// 		ms->flexit = 1;
// 		return ;
// 	}
// 	// if (DEBUG)
// 		printf(KYEL "-------------------- FT_MSH_ECHO" KRED " END " RT KYEL "--------------------\n" RT);
// }
