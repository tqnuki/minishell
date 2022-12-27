/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 09:15:49 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/27 14:40:35 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_s;
// Takes args as a splitted command by ' ' ex : "echo / uwu / | / grep / u"
// And line as the whole command ex : "echo uwu | grep u"

// Takes : args = {"echo", "uwu", "|", "grep", "u"} line = "echo uwu | grep u"
// Launch_executables takes : name = "grep" arguments = {"grep", "o"}

// I Return : 1 = "grep" / 2 = {"grep", "o", "|", "grep", "i"}

//Creer le fichier juste apres la redirection
//<< end cat > out
int	find_pos(char **av, char *str)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_strcmp(av[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_first_tab_split(char **args, char *str)
{
	int		i;
	int		j;
	char	**rep;

	j = 0;
	while (args[j] && ft_strcmp(args[j], str) != 0)
		j++;
	rep = malloc(sizeof(char *) * (j + 1));
	i = -1;
	while (++i < j)
		rep[i] = malloc(sizeof(char) * (ft_strlen(args[i]) + 1));
	i = 0;
	while (args[i] && ft_strcmp(args[i], str) != 0)
	{
		rep[i] = args[i];
		i++;
	}
	rep[i] = NULL;
	return (rep);
}

void	right_arrow(char **args, char *line, int mode, char *arrow)
{
	int	fd;
	int	cpy;

	fd = open(args[find_pos(args, arrow) + 1], mode, 0777);
	if (fd < 0)
		perror("ERROR");
	cpy = dup(1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	args = ft_first_tab_split(args, arrow);
	g_s->thing = launch(args, ft_strtrim(ft_single_split(line, '>')[0], " "));
	dup2(cpy, STDOUT_FILENO);
}
