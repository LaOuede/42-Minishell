#include "../include/minishell.h"

char	*ft_strjoin_free(char *str1, char *str2)
{
	printf(KYEL "-------------------- FT_STRJOIN_FREE" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!str1 || !str2)
		return (NULL);
	len = 0;
	len = ft_strlen(str1) + ft_strlen(str2);
	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);
	new_str = (char *)ft_calloc((len + 1), sizeof(char));
	i = 0;
	j = 0;
	while (str1[i])
		new_str[j++] = str1[i++];
	i = 0;
	while (str2[i])
		new_str[j++] = str2[i++];
	new_str[j] = '\0';
	if (str1)
		ft_freenull(str1);
	if (str2)
		ft_freenull(str2);
	printf(KYEL "-------------------- FT_STRJOIN_FREE" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	return (new_str);
}
