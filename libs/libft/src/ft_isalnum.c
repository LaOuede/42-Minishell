/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:23:06 by gle-roux          #+#    #+#             */
/*   Updated: 2023/02/09 21:31:19 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
Library :
	#include <ctype.h>
Description :
	The isalnum() function tests for any character for which isalpha(3) or 
	isdigit(3) is true. The value of the argument must be representable as an 
	unsigned char or the value of EOF.
Declaration :
	int	ft_isalnum(int c)
Parameters :
	c - The character to test.
Return value :
	The isalnum() function returns zero if the character tests false and returns 
	non-zero if the character tests true.
*/
int	ft_isalnum(int c)
{
	if ((ft_isalpha(c) == 1) || (ft_isdigit(c) == 1))
		return (1);
	return (0);
}
