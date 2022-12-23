/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpankewi <mpankewi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:04:08 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/23 11:54:34 by mpankewi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_s;

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

int	mini_execute(char **args, char *line)
{
	int	i;

	i = 0;
	if (!args[0])
		return (1);
	if (ft_strcmp(args[0], "exit") == 0)
		exit(0);
	pipeslmao(args, line);
	if (ft_strcmp(args[0], "cd") == 0)
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

//rl_replace_line("bash-6.9.$ ", 0);
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
	rl_initialize();
	g_s = malloc(sizeof(t_shell));
	g_s->env = malloc(100000);
	copy_char_array(env, g_s->env);
	loop();
	free(g_s->env);
}
