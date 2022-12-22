/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 utils6.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: mdoumi <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2022/12/22 16:27:34 by mdoumi			   #+#	  #+#			  */
/*	 Updated: 2022/12/22 16:45:46 by mdoumi			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell  *g_s;

void	amogus2(char *line, char **args, int i, char **tab)
{
	int j;

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
			break ;
		}
		tab[j++] = line;
	}
}

int launch2(char *dir, char *path, char *exec_path, char **arguments)
{
	int status;

	status = 0;
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
}

int launch3(char *name, int status, char **arguments, char *line)
{
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
	return (69);
}

void	amongusahh(char **args, char *str, int k, int i)
{
	int l;

	l = 0;
	if (ft_strcmp((args[i]), "$?") == 0)
		printf("%d", g_s->thing);
	else
	{
		while (args[i][k] && args[i][k] != '$')
			printf("%c", args[i][k++]);
		k++;
		while (args[i][k])
		{
			if (!ft_isalnum(args[i][k]))
			{
				printf("%s", get_value(g_s->env, str));
				while (args[i])
				{
					if (q && k == ft_strlen(args[i]) - 1)
						break ;
					printf("%c", args[i][k++]);
				}
			}
			str[l++] = args[i][k++];
			if (k == ft_strlen(args[i]) - 1)
				break ;
		}
		printf("%s", get_value(g_s->env, str));
	}
}
