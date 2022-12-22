/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 08:11:50 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/22 16:33:36 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_s;

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

int	strcmpeq(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (*s1++ && *s2++ && i++ < n)
	{
		if (*s1 == '=')
			return (0);
		if (*s1 != *s2)
			return (-1);
	}
	if ((!*s1 && !*s2) || i == n)
		return (0);
	else if (!*s1)
		return (-1);
	else
		return (1);
}

int	goofyahh(char **args)
{
	if (!args[1])
	{
		if (chdir(get_value(g_s->env, "HOME")))
			perror("ERROR");
		return (1);
	}
	if (args[1][0] == '~')
	{
		if (chdir(get_value(g_s->env, "HOME")))
			perror("ERROR");
		args[1] = trim_until_slash(args[1]);
		if (!args[1])
			return (1);
	}
	return (0);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

int	isdollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == '$')
			return (1);
	return (0);
}
