/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:34:01 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/19 11:49:19 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	g_s;

int	goofyahh(char **args)
{
	if (!args[1])
	{
		if (chdir(get_value(g_s.env, "HOME")))
			perror("ERROR");
		return (1);
	}
	if (args[1][0] == '~')
	{
		if (chdir(get_value(g_s.env, "HOME")))
			perror("ERROR");
		args[1] = trim_until_slash(args[1]);
		if (!args[1])
			return (1);
	}
	return (0);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

void	goofyahh2(char **args, int i, char *str)
{
	int	l;
	int	k;

	k = 0;
	l = 0;
	if (ft_strcmp((args[i]), "$?") == 0)
		printf("%d", g_s.thing);
	else if (isdollar(args[i]))
	{
		while (args[i][k] && args[i][k] != '$')
			printf("%c", args[i][k++]);
		k++;
		while (args[i][k])
			str[l++] = args[i][k++];
		printf("%s", get_value(g_s.env, str));
	}
	else
		printf("%s", args[i]);
	if (args[i + 1])
		printf(" ");
}

void	mini_unset(char *str)
{
	delete_char_ptr(g_s.env, str);
}
