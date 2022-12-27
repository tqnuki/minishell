/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:40:41 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/27 14:40:49 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_first_command(int fd[], char **args, char *line)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	launch_executable(ft_split(args[0], ' ')[0], ft_split(args[0], ' '),
		ft_strtrim(ft_single_split(line, '|')[1], " "));
}

void	execute_second_command(int fd[], char **args, char *line)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	launch_executable(ft_split(args[1], ' ')[0], ft_split(args[1], ' '),
		ft_strtrim(ft_single_split(line, '|')[1], " "));
}

void	pipe_execute(char **args, char *line)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	args = ft_single_split(line, '|');
	trim(args);
	if (pipe(fd) == -1)
		perror("ERROR");
	pid1 = fork();
	if (pid1 < 0)
		perror("ERROR");
	if (pid1 == 0)
		execute_first_command(fd, args, line);
	pid2 = fork();
	if (pid2 < 0)
		perror("ERROR");
	if (pid2 == 0)
		execute_second_command(fd, args, line);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
