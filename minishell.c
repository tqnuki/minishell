/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:59:40 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/27 11:03:17 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_s;

#include <string.h>

int launch_executable(char *name, char *arguments[], char *line)
{
    char *path;
    char *exec_path;
    char *dir;
    char **tmp;
	int status;

	status = 0;
    if (name[0] == '/')
    {
        status = execve(name, arguments, g_s->env);
        if (status == -1)
        {
            perror("execve failed");
            return 1;
        }
        return status;
    }
    if (pippin("|", arguments) == 1)
    {
        pipe_execute(arguments, line);
        return 0;
    }
    path = get_value(g_s->env, "PATH");
    if (path == NULL)
    {
        printf("Error: PATH environment variable not set\n");
        return 1;
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
                return 1;
            }
            return status;
        }
        dir = ft_strtok(NULL, ":");
    }
    printf("Error: executable '%s' not found\n", name);
    return 1;
}

int launch(char **args, char *line)
{
    pid_t pid;

    pid = fork();
    g_s->thing = 0;
    if (pid < 0)
        perror("ERROR");
    if (pid)
    {
        int child_status;
        waitpid(pid, &child_status, 0);
        if (WIFEXITED(child_status))
            return WEXITSTATUS(child_status);
        else
            return 1;
    }
    if (!pid)
        exit(launch_executable(args[0], args, line));
    return 1;
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

int	mini_execute(char **args, char *line)
{
	int	i;

	i = 0;
	if (!args[0])
		return (1);
	if (ft_strcmp(args[0], "exit") == 0)
		exit(0);
	else if (pippin("|", args) == 1)
		pipe_execute(args, line);
    else if (pippin("<", args) == 1)
        sussy(args, line);
	else if (pippin(">", args) == 1)
		right_arrow(args, line, O_WRONLY | O_CREAT | O_TRUNC, ">");
	else if (pippin(">>", args) == 1)
		right_arrow(args, line, O_RDWR | O_CREAT | O_APPEND, ">>");
    else if (pippin("<<", args) == 1)
        amongus(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		mini_cd(args);
	else if (ft_strcmp(args[0], "echo") == 0)
		mini_echo(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(args[0], "unset") == 0)
		mini_unset(args[1]);
	else if (ft_strcmp(args[0], "export") == 0)
		mini_export(args[1]);
	else if (ft_strcmp(args[0], "env") == 0)
		mini_env();
	else
		g_s->thing = launch(args, line);
	return (1);
}

void	signalhandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\nbash-6.9.$ ");
		signal(SIGQUIT, signalhandler);
	}
	if (sig == SIGQUIT)
		signal(SIGINT, signalhandler);
}

void	loop(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		signal(SIGINT, signalhandler);
		signal(SIGQUIT, signalhandler);
		line = readline("bash-6.9.$ ");
		if (!line)
			exit(0);
		add_history(line);
		args = ft_split(line, ' ');
		status = mini_execute(args, line);
		free(line);
		free(args);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_s = malloc(sizeof(t_shell));
	g_s->env = malloc(100000);
	copy_char_array(env, g_s->env);
	loop();
	free(g_s->env);
}
