/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpankewi <mpankewi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:58:13 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/23 11:43:09 by mpankewi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_s;

void	amogus2(char *line, char **args, int i, char **tab)
{
	int	j;

	j = 0;
	while (1)
	{
		line = readline("amogus ඞ ");
		if (ft_strcmp(line, args[i]) == 0)
		{
			j = 0;
			while (tab[j])
				printf("%s\n", tab[j++]);
			free(tab);
			return ;
		}
		tab[j++] = line;
	}
}

void	amongusahh(char **args, char *str, int i)
{
	int	l;
	int	k;

	k = 0;
	l = 0;
	if (g_s->q)
		k++;
	if (ft_strcmp((args[i]), "$?") == 0)
		printf("%d", g_s->thing);
	else
	{
		while (args[i][k] && args[i][k] != '$')
			printf("%c", args[i][k++]);
		k++;
		wtfisthisfunction(args, str, k, i);
		printf("%s", get_value(g_s->env, str));
	}
}

int	launchexec(char *exec_path, char **arguments, int status)
{
	if (access(exec_path, X_OK) == 0)
	{
		status = execve(exec_path, arguments, g_s->env);
		if (status == -1)
		{
			printf("execve failed");
			return (1);
		}
		return (status);
	}
	return (69);
}

int	launchex(char **arguments, char *name, char *path, char *exec_path)
{
	char	*dir;
	int		status;

	path = get_value(g_s->env, "PATH");
	if (path == NULL)
	{
		printf("Error: PATH environment variable not set\n");
		return (1);
	}
	dir = ft_strtok(path, ":");
	while (1)
	{
		exec_path = malloc(1000);
		ft_strcpy(exec_path, dir);
		ft_strlcat(exec_path, "/", 1000);
		ft_strlcat(exec_path, name, 1000);
		status = launchexec(exec_path, arguments, status);
		if (status != 69)
			return (status);
		dir = ft_strtok(NULL, ":");
	}
	printf("Error: executable '%s' not found\n", name);
	return (1);
}

int	launch_executable(char *name, char *arguments[], char *line)
{
	char	*path;
	char	*exec_path;
	char	*dir;
	char	**tmp;
	int		status;

	status = 0;
	if (name[0] == '/')
	{
		status = execve(name, arguments, g_s->env);
		if (status == -1)
		{
			perror("execve failed");
			return (1);
		}
		return (status);
	}
	if (pippin("|", arguments) == 1)
	{
		pipe_execute(arguments, ft_strtrim(ft_single_split(line, '|')[1], " "));
		return (0);
	}
	return (launchex(arguments, name, path, exec_path));
}
