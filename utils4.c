/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpankewi <mpankewi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:04:36 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/23 11:15:30 by mpankewi         ###   ########.fr       */
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
	static char	*saved_str;
	char		*start;
	char		*end;

	if (str == NULL)
		str = saved_str;
	if (str == NULL)
		return (NULL);
	start = str;
	while (*start && ft_strchr(delim, *start))
		start++;
	if (!*start)
		return (saved_str = NULL);
	end = start;
	while (*end && !ft_strchr(delim, *end))
		end++;
	if (*end != '\0')
	{
		*end = '\0';
		saved_str = end + 1;
	}
	else
		saved_str = NULL;
	return (start);
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
}
