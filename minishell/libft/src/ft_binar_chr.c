/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binar_chr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwing <cwing@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 00:59:16 by cwing             #+#    #+#             */
/*   Updated: 2020/05/07 20:36:16 by cwing            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_binar_chr(char *str, char item)
{
	int		low;
	int		high;
	int		mid;
	char	*guess;

	low = 0;
	high = ft_strlen((const char *)str);
	while (low <= high)
	{
		mid = (low + high) / 2;
		guess = &str[mid];
		if (*guess == item)
			return (&str[mid]);
		if (*guess > item)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return (NULL);
}
