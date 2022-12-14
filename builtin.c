/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:26:50 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/22 15:26:53 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_s;

void	mini_pwd(void)
{
	int	i;
	int	j;

	i = 0;
	g_s->thing = 0;
	while (g_s->env[i])
	{
		if (g_s->env[i][0] == 'P' && g_s->env[i][1] == 'W'
				&& g_s->env[i][2] == 'D' && g_s->env[i][3] == '=')
		{
			j = 4;
			while (g_s->env[i][j])
				write(1, &g_s->env[i][j++], 1);
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
	if (!str)
		return ;
	str = trim_quotes(str);
	if (!str)
		return ;
	while (g_s->env[i])
		i++;
	g_s->env[i] = malloc(1000);
	ft_strcpy(g_s->env[i], str);
}

void	mini_env(void)
{
	int	i;

	i = 0;
	g_s->thing = 0;
	while (g_s->env[i])
		printf("%s\n", g_s->env[i++]);
}

void	mini_echo(char **args)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	if (echouwu(args) == 1)
		return ;
	str = malloc(1000);
	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "-n") == 0)
		{
			i++;
			j = 1;
		}
		else
			break ;
	}
	goofyahh2(args, i, str);
	if (j != 1)
		printf("\n");
	g_s->thing = 0;
	free(str);
}

int	mini_cd(char **args)
{
	char	*str;

	g_s->thing = 0;
	if (!args[1])
	{
		chdir(get_value(g_s->env, "HOME"));
		mini_unset("PWD");
		str = getcwd(NULL, 0);
		prepend(str, "PWD=");
		mini_export(str);
		return (1);
	}
	args[1] = trim_quotes(args[1]);
	if (goofyahh(args) == 1)
		return (1);
	g_s->thing = chdir(args[1]);
	if (g_s->thing)
		perror("ERROR");
	if (g_s->thing == -1)
		g_s->thing = 1;
	str = getcwd(NULL, 0);
	prepend(str, "PWD=");
	mini_unset("PWD");
	mini_export(str);
	return (1);
}
