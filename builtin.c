/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:54:28 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/19 11:14:25 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	g_s;

void	mini_pwd(void)
{
	int	i;
	int	j;

	i = 0;
	g_s.thing = 0;
	while (g_s.env[i])
	{
		if (g_s.env[i][0] == 'P' && g_s.env[i][1] == 'W'
				&& g_s.env[i][2] == 'D' && g_s.env[i][3] == '=')
		{
			j = 4;
			while (g_s.env[i][j])
				write(1, &g_s.env[i][j++], 1);
			write(1, "\n", 1);
			return ;
		}
		i++;
	}
}

void	mini_export(char *str)
{
	int	i;

	i = 0;
	while (g_s.env[i])
		i++;
	g_s.env[i] = malloc(1000);
	ft_strcpy(g_s.env[i], str);
}

void	mini_env(void)
{
	int	i;

	i = 0;
	g_s.thing = 0;
	while (g_s.env[i])
		printf("%s\n", g_s.env[i++]);
}

void	mini_echo(char **args)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*str;

	i = 1;
	j = 0;
	k = 0;
	l = 0;
	str = malloc(1000);
	while (args[i])
	{
		if (strcmp(args[i], "-n") == 0)
		{
			i++;
			j = 1;
		}
		else
			break ;
	}
	while (args[i])
	{
		if (strcmp((args[i]), "$?") == 0)
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
		if (args[i +1])
			printf(" ");
		i++;
	}
	if (j != 1)
		printf("\n");
	g_s.thing = 0;
	free(str);
}

void	mini_unset(char *str)
{
	delete_char_ptr(g_s.env, str);
}

int	mini_cd(char **args)
{
	char	*str;

	g_s.thing = 0;
	str = malloc(10000);
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
	g_s.thing = chdir(args[1]);
	if (g_s.thing)
		perror("ERROR");
	if (g_s.thing == -1)
		g_s.thing = 1;
	str = getcwd(NULL, 0);
	prepend(str, "PWD=");
	mini_unset("PWD");
	mini_export(str);
	free(str);
	return (1);
}
