/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:34:01 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/20 08:48:25 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	g_s;

char	*trim_until_slash(char *str)
{
	char	*slash_pos;

	slash_pos = ft_strchr(str, '/');
	if (slash_pos == NULL)
		return (NULL);
	else
		return (slash_pos + 1);
}

char	*get_value(char **lines, const char *key)
{
	int		i;
	char	*equals_pos;

	i = 0;
	while (lines[i])
	{
		if (ft_strncmp(lines[i], key, ft_strlen(key)) == 0)
		{
			equals_pos = ft_strchr(lines[i], '=');
			if (equals_pos == NULL)
				return ("");
			else
				return (equals_pos + 1);
		}
		i++;
	}
	return ("");
}

int	pippin(char *str, char **av)
{
	int	i;

	i = -1;
	while (av[++i])
		if (av[i][0] == str[0] && av[i][1] == '\0' && str[1] == '\0')
			return (1);
	return (0);
}

static void	trim(char **av)
{
	int	i;

	i = -1;
	while (av[++i])
		av[i] = ft_strtrim(av[i], " ");
}

void	pipe_execute(char **args, char *line)
{
	int	fd[2];

	args = ft_single_split(line, '|');
	trim(args);
	if (pipe(fd) == -1)
		perror("ERROR");

	int pid1 = fork();
	if (pid1 < 0)
		perror("ERROR");

	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		mini_execute(args[0], args[0]);
	}

	int pid2 = fork();
	if (pid2 < 0)
		perror("ERROR");

	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		mini_execute(args[1], args[1]);
	}

	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return ;
}

//int	main()
//{
	//char **tab;

	//tab = malloc(sizeof(char *) * 10);
	//for (int i = 0; i < 10; i++)
		//tab[i] = malloc(sizeof(char) * 10);
	//tab[0] = "Bonsoir";
	//tab[1] = "Je";
	//tab[2] = "|";
	//tab[3] = "Suis";
	//tab[4] = "Cool";

	//printf("%d\n", pippin("|s", tab));
//}
