/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:59:40 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/19 13:03:05 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_s;

int	launch(char **args)
{
	pid_t	pid;

	g_s.thing = 0;
	pid = fork();
	prepend(args[0], "/bin/");
	if (!pid)
	{
		g_s.thing = execve(args[0], args, g_s.env);
		if (g_s.thing == -1)
			perror("ERROR");
		exit(0);
	}
	else if (pid < 0)
		perror("ERROR");
	return (1);
}

int	mini_execute(char **args, char *line)
{
	int	i;

	i = 0;
	if (!args[0])
		return (1);
	if (ft_strcmp(args[0], "exit") == 0)
		exit(0);
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
		launch(args);
	while (i < 100000000)
		i++;
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
	g_s.env = malloc(10000);
	copy_char_array(env, g_s.env);
	loop();
	free(g_s.env);
}
