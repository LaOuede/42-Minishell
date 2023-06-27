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
	(void)ms;
	if (cmd[2])
	{
		ft_putstr_fd("Too many args\nUsage: env [no opt/args]\n", 2);
		return ;
	}
	else if (chdir(cmd[1]) != 0)
	{
		perror("Error! chdir");
		exit(127); //TODO quel code erreur ?
	}
}
