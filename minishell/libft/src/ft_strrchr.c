/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwing <cwing@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 23:45:53 by cwing             #+#    #+#             */
/*   Updated: 2020/05/07 20:42:57 by cwing            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ss;

	ss = (char*)(s);
	i = ft_strlen(ss);
	while (i >= 0)
	{
		if (ss[i] == c)
			return (&ss[i]);
		--i;
	}
	return (NULL);
}
