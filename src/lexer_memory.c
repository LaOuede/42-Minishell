#include "../include/minishell.h"

char	*ft_mem_alloc(char *str, int capacity)
{
	int		i;
	char	*new;

	new = ft_calloc(sizeof(new), (capacity * 2));
	if (!new)
		return (0);
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

char	*ft_strjoin_char(const char *s1, const char s2)
{
	size_t	i;
	char	*s3;
	size_t	len;

	len = (ft_strlen(s1) + 1);
	s3 = ft_calloc((len + 1), sizeof(char));
	if (!s3)
		return (0);
	len = 0;
	while (s1[len])
	{
		s3[len] = s1[len];
		len++;
	}
	i = 0;
	s3[len + i] = s2;
	free((char *)s1);
	return (s3);
}
