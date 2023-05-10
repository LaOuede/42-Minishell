/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:41:05 by gle-roux          #+#    #+#             */
/*   Updated: 2023/03/06 14:53:10 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Library :
	#include <ctype.h>
Description : 
	The ft_str_isdigit() function tests for a string and checks if each
	character of the string is a digit.
Declaration :
	int	ft_str_isdigit(str *str)
Parameters :
	str - The string to test.
Return value :
	The str_isdigit() function returns zero if a character tests false and 
	returns 1 if all characters in the string are digits.
*/
int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (48 <= str[i] && str[i] <= 57)
			i++;
		else
			return (0);
	}
	return (1);
}
