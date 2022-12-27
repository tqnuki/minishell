/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 16:31:45 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/27 19:06:29 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_s;

void	mini_unset(char *str)
{
	int	i;
	int	boul;

	i = -1;
	boul = 0;
	if (!str)
		return ;
	str = trim_quotes(str);
	if (!str)
		return ;
	while (boul == 0 && g_s->env[++i])
		if (ft_strcmp(ft_split(g_s->env[i], '=')[0], str) == 0)
			boul = 1;
	if (boul == 1)
	{
		while (g_s->env[i + 1])
		{
			g_s->env[i] = g_s->env[i + 1];
			i++;
		}
		g_s->env[i] = NULL;
	}
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
		pipe_execute(arguments, line);
		return (0);
	}
	path = get_value(g_s->env, "PATH");
	if (path == NULL)
	{
		printf("Error: PATH environment variable not set\n");
		return (1);
	}
	dir = ft_strtok(path, ":");
	while (dir != NULL)
	{
		exec_path = malloc(1000);
		ft_strcpy(exec_path, dir);
		ft_strlcat(exec_path, "/", 1000);
		ft_strlcat(exec_path, name, 1000);
		if (access(exec_path, X_OK) == 0)
		{
			status = execve(exec_path, arguments, g_s->env);
			if (status == -1)
			{
				perror("execve failed");
				return (1);
			}
			return (status);
		}
		dir = ft_strtok(NULL, ":");
	}
	printf("Error: executable '%s' not found\n", name);
	return (1);
}

int	launch(char **args, char *line)
{
	pid_t	pid;
	int		child_status;

	pid = fork();
	g_s->thing = 0;
	if (pid < 0)
		perror("ERROR");
	if (pid)
	{
		waitpid(pid, &child_status, 0);
		if (WIFEXITED(child_status))
			return (WEXITSTATUS(child_status));
		else
			return (1);
	}
	if (!pid)
		exit(launch_executable(args[0], args, line));
	return (1);
}

void	sussy(char **args, char *line)
{
	int	fd;
	int	cpy;

	fd = open(args[find_pos(args, "<") + 1], O_RDONLY, 0777);
	if (fd < 0)
		perror("ERROR");
	if (find_pos(args, "<") != 0)
	{
		cpy = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		close(fd);
		args = ft_first_tab_split(args, "<");
		g_s->thing = launch(args,
				ft_strtrim(ft_single_split(line, '<')[0], " "));
		dup2(cpy, STDIN_FILENO);
	}
	else
		sussy2(args);
}

void	sussy2(char **args)
{
	char	*buf;
	int		rd;
	int		fd;

	fd = open(args[1], O_RDONLY);
	buf = malloc(10);
	while (rd && rd != -1)
	{
		rd = read(fd, buf, 1);
		printf("%s", buf);
	}
}
