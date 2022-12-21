/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:34:01 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/20 13:14:2 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_s;

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

// Takes args as a splitted command by ' ' ex : "echo / uwu / | / grep / u"
// And line as the whole command ex : "echo uwu | grep u"

// Takes : args = {"echo", "uwu", "|", "grep", "u"} line = "echo uwu | grep u"
// Launch_executables takes : name = "grep" arguments = {"grep", "o"}

// I Return : 1 = "grep" / 2 = {"grep", "o", "|", "grep", "i"}
void	pipe_execute(char **args, char *line)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	args = ft_single_split(line, '|');
	trim(args);
	if (pipe(fd) == -1)
		perror("ERROR");
	pid1 = fork();
	if (pid1 < 0)
		perror("ERROR");
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		launch_executable(ft_split(args[0], ' ')[0], ft_split(args[0], ' '), line);
	}
	pid2 = fork();
	if (pid2 < 0)
		perror("ERROR");
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		launch_executable(ft_split(args[1], ' ')[0], ft_split(args[1], ' '), line);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return ;
}
