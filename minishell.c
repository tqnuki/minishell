/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpankewi <mpankewi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:10:15 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/18 16:39:02 by mpankewi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

typedef struct s_shell
{
	char **env;
	int thing;
}		t_shell;

t_shell s;

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
size_t	ft_strlen(const char *str)
{
	int	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}
size_t	ft_strlcpy(char *dest, const char *src)
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
void copy_char_array(char** source, char** dest) {
  int i;
  i = 0;
  while (source[i]) {
	dest[i] = malloc(1000);
    ft_strlcpy(dest[i], source[i]);
	i++;
  }
}
char	*ft_strnstr(const char *haystack, const char *to_find, size_t size)
{
	size_t	a;
	size_t	b;
	char	*str;

	str = (char *) haystack;
	a = 0;
	b = 0;
	if (to_find[a] == '\0')
		return (str);
	if (!size)
		return (0);
	while (str[a] && size)
	{
		while (str[a + b] == to_find[b] && str[a + b] && a + b < size)
			b++;
		if (!to_find[b])
			return (str + a);
		a++;
		b = 0;
	}
	return (0);
}
char *get_value(char **lines, const char *key) {
	for (int i = 0; lines[i] != NULL; i++) {
		if (strncmp(lines[i], key, strlen(key)) == 0) {
    		char *equals_pos = strchr(lines[i], '=');
			if (equals_pos == NULL)
				return "";
      		else
        		return equals_pos + 1;
      }
    }
	return "";
  }
void prepend(char* s, const char* t)
{
    size_t len = strlen(t);
    memmove(s + len, s, strlen(s) + 1);
    memcpy(s, t, len);
}
char *trim_until_slash(char *str) {
  char *slash_pos = strchr(str, '/');
  if (slash_pos == NULL)
    return NULL;
  else
    return slash_pos + 1;
}
int strcmpeq(const char *s1, const char *s2, int n) {
	int i = 0;
	while (*s1 && *s2 && i < n) {
    	if (*s1 == '=')
    	  return 0;
    	if (*s1 != *s2)
    	  return (-1);
    	s1++;
    	s2++;
		i++;
	}
	if(i == n)
		return(0);
 	if (!*s1 && !*s2)
    	return 0;
	else if (!*s1)
    	return -1;
	else
		return 1;
}
void delete_char_ptr(char **str_arr, char *str) {
  char **ptr = str_arr;
  while(*ptr) {
    if(strcmpeq(*ptr, str, strlen(str)) == 0) {
      while(*ptr) {
        *ptr = *(ptr + 1);
        ptr++;
      }
      break;
    }
    ptr++;
  }
}
char *findString(char **strings, char *startString)
{
	int i = 0;
	while (strings[i] != NULL)
	{
		if (strncmp(strings[i], startString, strlen(startString)) == 0)
			return strings[i];
		i++;
	}
	return NULL;
}
int launch(char **args)
{
	s.thing = 0;
	pid_t pid, wpid;
	int status;
	pid = fork();
	prepend(args[0], "/bin/");
	if (!pid) {
	  if ((s.thing = execve(args[0], args, s.env)) == -1)
		perror("ERROR");
	  exit(0);
	}
	else if (pid < 0)
	  perror("ERROR");
	return (1);
}

void mini_pwd()
{
	int i = 0;
	int j;
	s.thing = 0;
	while(s.env[i])
	{
		if (s.env[i][0] == 'P' && s.env[i][1] == 'W' && s.env[i][2] == 'D' && s.env[i][3] == '='){
			j = 4;
			while(s.env[i][j])
				write(1, &s.env[i][j++], 1);
			write(1, "\n", 1);
			return ;
		}
		i++;
	}	
	
}


void mini_export(char *str)
{
	int i = 0;
	while(s.env[i])
		i++;
	s.env[i] = malloc(1000);
	ft_strlcpy(s.env[i], str);
	
}

void mini_env()
{
	s.thing = 0;
	int i = 0;
	while (s.env[i])
		printf("%s\n", s.env[i++]);
}

int isdollar(char *str)
{
	int i = 0;
	while(str[i])
		if(str[i++] == '$')
			return(1);
	return(0);
}

void mini_echo(char **args)
{
	int i = 1;
	int j = 0;
	char *str = malloc(1000);
	while(args[i])
	{
		if(strcmp(args[i], "-n")==0){
			i++;	
			j = 1;
		}
		else
			break;
	}
	while(args[i])
	{
		if(strcmp((args[i]), "$?") == 0)
			printf("%d", s.thing);
		else if (isdollar(args[i]))
		{
			int k = 0;
			int l = 0;
			while(args[i][k] && args[i][k] != '$')
				printf("%c", args[i][k++]);
			k++;
			while(args[i][k])
				str[l++] = args[i][k++];
			printf("%s", get_value(s.env, str));
		}
		else
			printf("%s", args[i]);
		if(args[i+1])
			printf(" ");
		i++;
	}
	if(j != 1)
		printf("\n");
	s.thing = 0;
	free(str);
}

void mini_unset(char *str)
{
	delete_char_ptr(s.env, str);
}


int mini_cd(char **args)
{
	char *str;
	s.thing = 0;
	str = malloc(10000);
	if (!args[1]){
		if (chdir(get_value(s.env, "HOME")))
			perror("ERROR");
		return (1);}
	if(args[1][0] == '~'){
		if (chdir(get_value(s.env, "HOME")))
			perror("ERROR");
		args[1] = trim_until_slash(args[1]);
		if(!args[1])
			return(1);}
	s.thing = chdir(args[1]);
	if (s.thing)
    	perror("ERROR");
	if(s.thing == -1)
		s.thing = 1;
	str = getcwd(NULL, 0);
	prepend(str, "PWD=");
	mini_unset("PWD");
	mini_export(str);
	free(str);
  	return (1);
}

int mini_execute(char **args, char *line)
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

void signalHandler(int signal) {
    switch(signal) {
        case SIGINT:
			printf("\nbash-6.9.$ ");
            break;
        case SIGQUIT:
            break;
        case SIGTSTP:
            exit(0);
    }
} 

void loop()
{
	char *line;
	char **args;
	int status = 1;
	while(status)
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
	s.env = malloc(10000);
	
	copy_char_array(env, s.env);
	//for (int i = 0; env[i]; i++)
	//{
	//	printf("ENV : %s\n", env[i]);
	//	printf("BETTER ENV : %s\n", s.env[i]);
	//}
	loop();
	free(s.env);
}
