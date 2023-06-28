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

void	ft_msh_cd(t_ms *ms, char **cmd)
{
	// if (DEBUG)
		printf(KYEL "-------------------- FT_MSH_CD" KGRN " START " RESET KYEL "--------------------\n" RESET);
	(void)ms;
	int	ac;
	char *user;
	
	user = getenv("HOME");
	ac = ft_get_ac(cmd);
	printf("ac: %d\n", ac);
	if (ac < 2 || ft_strcmp(cmd[1], "~") == 0)
	{
		if(chdir(user) != 0)
			perror("Error! chdir");
	}
	else if (ac < 3 && chdir(cmd[1]) != 0)
	{
		perror("Error! chdir");
		ms->flexit = 1;
		return ;
		// exit(127); //TODO quel code erreur ?
	}
	else if(ac >= 3)
	{
		ft_putstr_fd("Too many args\nUsage: env [no opt/args]\n", 2);
		return ;
	}
	// if (DEBUG)
		printf(KYEL "-------------------- FT_MSH_ECHO" KRED " END " RESET KYEL "--------------------\n" RESET);
}
