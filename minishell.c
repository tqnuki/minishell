/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:59:40 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/19 11:14:25 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_s;

void	copy_char_array(char **source, char **dest)
{
	int	i;

	i = 0;
	while (source[i])
	{
		dest[i] = malloc(1000);
		ft_strcpy(dest[i], source[i]);
		i++;
	}
}

char	*get_value(char **lines, const char *key)
{
	int i;
	char *equals_pos;

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

void	prepend(char *s, const char *t)
{
	size_t len;

	len = ft_strlen(t);
	ft_memmove(s + len, s, ft_strlen(s) + 1);
	ft_memcpy(s, t, len);
}

char	*trim_until_slash(char *str)
{
	char	*slash_pos;

	slash_pos = ft_strchr(str, '/');
	if (slash_pos == NULL)
		return (NULL);
  	else
		return (slash_pos + 1);
}

int	strcmpeq(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (*s1++ && *s2++ && i++ < n)
	{
		if (*s1 == '=')
		  return (0);
		if (*s1 != *s2)
		  return (-1);
	}
	if ((!*s1 && !*s2) || i == n)
		return (0);
	else if (!*s1)
		return (-1);
	else
		return (1);
}

void	delete_char_ptr(char **str_arr, char *str)
{
	char	**ptr;

	ptr = str_arr;
	while (*ptr)
	{
		if (strcmpeq(*ptr, str, ft_strlen(str)) == 0)
		{
			while (*ptr++)
				*ptr = *(ptr + 1);
		break;
		}
	ptr++;
	}
}

char	*findString(char **strings, char *startString)
{
	int i;

	i = 0;
	while (strings[i] != NULL)
	{
		if (ft_strncmp(strings[i], startString, ft_strlen(startString)) == 0)
			return (strings[i]);
		i++;
	}
	return (NULL);
}

int	launch(char **args)
{
	pid_t pid;

	g_s.thing = 0;
	pid = fork();
	prepend(args[0], "/bin/");
	if (!pid)
	{
		if ((g_s.thing = execve(args[0], args, g_s.env)) == -1)
			perror("ERROR");
		exit(0);
	}
	else if (pid < 0)
		perror("ERROR");
	return (1);
}

int isdollar(char *str)
{
	int i;

	i = 0;
	while (str[i])
		if (str[i++] == '$')
			return (1);
	return (0);
}

int	mini_execute(char **args, char *line)
{
	int	i;

	i = 0;
	if (!args[0])
		return (1);
	if (strcmp(args[0], "exit") == 0)
		exit(0);
	else if (strcmp(args[0], "cd") == 0)
		mini_cd(args);
	else if (strcmp(args[0], "echo") == 0)
		mini_echo(args);
	else if (strcmp(args[0], "pwd") == 0)
		mini_pwd();
	else if (strcmp(args[0], "unset") == 0)
		mini_unset(args[1]);
	else if (strcmp(args[0], "export") == 0)
		mini_export(args[1]);
	else if (strcmp(args[0], "env") == 0)
		mini_env();
	else
		launch(args);
	usleep(10000);
	return (1);
}

void	signalHandler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\nbash-6.9.$ ");
		break;
	}
	if(signal == SIGQUIT)

		case SIGTSTP:
			exit(0);

}

void	loop()
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		signal(SIGINT, signalHandler);
		signal(SIGQUIT, signalHandler);
		signal(SIGTSTP, signalHandler);
		line = readline("bash-6.9.$ ");
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
