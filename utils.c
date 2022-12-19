/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 08:11:50 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/19 10:02:16 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	int	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}
size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	a;

	a = 0;
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (ft_strlen(src));
}

char	*ft_strnstr(const char *haystack, const char *to_find, size_t size)
{
	size_t	a;
	size_t	b;
	char	*str;

	str = (char *) haystack;
	a = 0;
	b = 0;
	if (to_find[a] == '\0')
		return (str);
	if (!size)
		return (0);
	while (str[a] && size)
	{
		while (str[a + b] == to_find[b] && str[a + b] && a + b < size)
			b++;
		if (!to_find[b])
			return (str + a);
		a++;
		b = 0;
	}
	return (0);
}
