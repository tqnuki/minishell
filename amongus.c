/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amongus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 16:29:48 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/27 16:31:09 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input_lines(char ***tab, int *j, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("amogus ඞ ");
		if (ft_strcmp(line, delimiter) == 0)
		{
			break ;
		}
		(*tab)[(*j)] = line;
		(*j)++;
	}
}

void	print_input_lines(char **tab)
{
	int	j;

	j = 0;
	while (tab[j])
	{
		printf("%s\n", tab[j++]);
	}
}

void	remove_delimiter_and_following_args(char **args, char *delimiter)
{
	int	i;

	i = 0;
	while (args[i] && ft_strcmp(args[i], delimiter) != 0)
	{
		i++;
	}
	while (args[i])
	{
		args[i] = NULL;
		i++;
	}
}

void	amongus(char **args)
{
	char	**tab;
	int		j;
	int		i;

	j = 0;
	i = 0;
	tab = malloc(10000);
	while (args[i] && ft_strcmp(args[i], "<<") != 0)
	{
		i++;
	}
	i++;
	read_input_lines(&tab, &j, args[i]);
	print_input_lines(tab);
	free(tab);
	remove_delimiter_and_following_args(args, "<<");
	mini_execute(args, "");
}

int	check_unclosed_quotes(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (!s)
		return (1);
	if (s[0] == '\'' || s[0] == '"')
	{
		if (s[0] != s[len - 1])
		{
			printf("Error: unclosed quotes\n");
			return (1);
		}
	}
	return (0);
}
