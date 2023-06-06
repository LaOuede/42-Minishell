#include "../include/minishell.h"

char	*ft_mem_alloc(char *str, int capacity)
{
	int		i;
	char	*new;

	new = ft_calloc(sizeof(new), (capacity * 2));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	free(str);
	return (new);
}

char	*ft_stock_char(char *str, char c)
{
	static int	i = 0;
	static int	size = 0;
	static int	capacity = 2;

	if (!str)
	{
		i = 0;
		size = 0;
		capacity = 2;
		str = ft_calloc(sizeof(str), capacity);
	}
	str[i++] = c;
	if (size++ == capacity)
	{
		str = ft_mem_alloc(str, capacity);
		capacity *= 2;
	}
	return (str);
}

char	*ft_strjoin_char(char *s1, char s2)
{
	printf(KYEL "-------------------- FT_STRJOIN_CHAR" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*s3;
	size_t	len;

	len = (ft_strlen(s1));
	s3 = ft_calloc((len + 2), sizeof(char));
	if (!s3)
		return (0);
	len = 0;
	while (s1[len])
	{
		printf("char = %c\n", s1[len]);
		s3[len] = s1[len];
		len++;
	}
	printf("len = %zu\n", len);
	s3[len] = s2;
	printf("s3 = %s\n", s3);
	ft_freenull(s1);
	printf(KYEL "-------------------- FT_STRJOIN_CHAR" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	return (s3);
}
