/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:26:47 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/22 16:45:32 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pippin(char *str, char **av)
{
	int	i;

	i = -1;
	while (av[++i])
		if (ft_strcmp(av[i], str) == 0)
			return (1);
	return (0);
}

void	trim(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		av[i] = ft_strtrim(av[i], " ");
		i++;
	}
}

char	**cupid(char *str)
{
	char	**rep;

	rep = malloc(sizeof(char *) * 2);
	rep[0] = ft_strdup(str);
	rep[1] = NULL;
	return (rep);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*s;
	size_t		i;
	char		*temp;

	i = 0;
	s = NULL;
	if (str != NULL)
		s = str;
	if (s == NULL || *s == '\0')
		return (NULL);
	while (s[i] != '\0' && ft_strchr(delim, s[i]) == NULL)
		i++;
	if (s[i] == '\0')
	{
		temp = s;
		s = NULL;
		return (temp);
	}
	s[i] = '\0';
	temp = s;
	s += i + 1;
	return (temp);
}

void	amongus(char **args)
{
	int		i;
	int		j;
	char	**tab;
	char	*line;

	tab = malloc(10000);
	i = 0;
	while (args[i] && ft_strcmp(args[i], "<<") != 0)
		i++;
	i++;
	amogus2(line, args, i, tab);
	i = 0;
	while (args[i++])
		if (ft_strcmp(args[i], "<<") == 0)
			while (args[i])
				args[i++] = NULL;
	mini_execute(args, "");
}
