/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpankewi <mpankewi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:10:15 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/09 10:04:38 by mpankewi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>

#include <string.h>
static int	wordcount(const char *s, char c, int opt, char **strs)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (opt == 1)
	{
		while (s[i])
		{
			while (s[i] && s[i] == c)
				i++;
			if (s[i] && s[i] != c)
				count++;
			while (s[i] && s[i] != c)
				i++;
		}
		return (count);
	}
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (1);
}
static int	wordlen(const char *s, char c, int i)
{
	int	i2;

	i2 = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		i2++;
	}
	return (i2);
}
static char	*putword(const char *str, char charset, int i)
{
	char	*rep;
	int		len;
	int		j;

	j = 0;
	if (!str)
		return (NULL);
	len = wordlen(str, charset, i);
	rep = malloc(sizeof(char) * (len + 1));
	if (!rep)
		return (NULL);
	while (str[i] && str[i] != charset)
	{
		rep[j] = str[i];
		j++;
		i++;
	}
	rep[j] = '\0';
	return (rep);
}
static char	**split2(const char *str, char charset, int j, int i)
{
	char	**rep;

	rep = NULL;
	rep = malloc(sizeof(char *) * (wordcount(str, charset, 1, rep) + 1));
	if (!rep)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == charset)
			i++;
		if (str[i] != '\0')
		{
			rep[j] = putword(str, charset, i);
			if (!rep[j++])
				if (wordcount(str, charset, 0, rep))
					return (NULL);
		}
		while (str[i] && str[i] != charset)
			i++;
	}
	rep[j] = 0;
	return (rep);
}
char	**ft_split(const char *str, char charset)
{
	char	**rep;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	rep = NULL;
	rep = split2(str, charset, j, i);
	if (!rep)
		return (NULL);
	return (rep);
}

int launch(char **args, char **env)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (!pid) {
	  if (execve(args[0], args, env) == -1)
	    perror("ERROR");
	  exit(0);
	}
	else if (pid < 0)
	  perror("ERROR");
	else {
		wpid = waitpid(pid, &status, WUNTRACED);
	  while (!WIFEXITED(status) && !WIFSIGNALED(status))
	    wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

int mini_cd(char **args)
{
	if (chdir(args[1]))
    	perror("ERROR");
  	return (1);
}

int mini_execute(char **args, char *line, char **env)
{
	int i;
	
	i = 0;
	if (!args[0]) {
    	return (1);
  	}
	i = 0;
    if (strcmp(args[0], "exit") == 0)
    	exit(0);
	else if (strcmp(args[0], "cd") == 0)
		mini_cd(args);
	//else if (strcmp(args[0], "echo") == 0)
	//else if (strcmp(args[0], "pwd") == 0)
	//else if (strcmp(args[0], "env") == 0)
	//else if (strcmp(args[0], "unset") == 0)
	//else if (strcmp(args[0], "export") == 0)
	return (launch(args, env));
}
 

void loop(char **env)
{
	char *line;
	char **args;
	int status = 1;
	while(status)
	{
		printf("【𝙼𝚒𝚗𝚒𝚜𝚑𝚎𝚕𝚕】> ");
		line = readline(NULL);
		args = ft_split(line, ' ');
		status = mini_execute(args, line, env);
		free(line);
		free(args);
	}
}

size_t	ft_strlen(const char *str)
{
	int	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}

int	ft_strrlen(char **env)
{
	int	i;

	i = 0;
	while(env[i])
		i++;
	return (i);
}

size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	a;

	a = 0;
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (ft_strlen(src));
}

char	**ft_strrcpy(char **env)
{
	int	i;
	char **rep;

	i = -1;
	rep = malloc(sizeof(char *) * ft_strrlen(env));
	while (++i < ft_strrlen(env))
		rep[i] = malloc(sizeof(char) * ft_strlen(env[i]));
	i = -1;
	while (++i < ft_strrlen(env))
		ft_strcpy(rep[i], env[i]);
	return (rep);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char **betterenv;
	betterenv = ft_strrcpy(env);
	betterenv[0] = "dustin moment";
	for (int i = 0; env[i]; i++)
	{
		printf("ENV : %s\n", env[i]);
		printf("BETTER ENV : %s\n", betterenv[i]);
	}
	//loop(betterenv);
	//free(betterenv);
}
