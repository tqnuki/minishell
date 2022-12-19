/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 08:17:12 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/19 10:36:19 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell s;

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
	ft_strcpy(s.env[i], str);

}

void mini_env()
{
	s.thing = 0;
	int i = 0;
	while (s.env[i])
		printf("%s\n", s.env[i++]);
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

