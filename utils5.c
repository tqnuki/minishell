/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpankewi <mpankewi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:29:53 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/23 16:01:15 by mpankewi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_s;

int	pip2(int fd[2], int pid2, char **p)
{
	pid2 = fork();
	if (pid2 < 0)
		return (-1);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		launch_executable(ft_split(p[1], ' ')[0], ft_split(p[1], ' '), p[1]);
		exit(0);
	}
	return (pid2);
}

void	piping(int fd[2], int pid1, int pid2, char **p)
{
	if (pipe(fd) == -1)
		perror("ERROR");
	pid1 = fork();
	if (pid1 < 0)
		return ;
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		launch_executable(ft_split(p[0], ' ')[0], ft_split(p[0], ' '), p[0]);
		exit(0);
	}
	pid2 = pip2(fd, pid2, p);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return ;
}

void	pipe_executee(char **args, char *line)
{
	int		fd[2];
	int		pid1;
	int		pid2;
	char	**p;

	p = ft_split(line, '|');
	piping(fd, pid1, pid2, p);
	return ;
}

void	pipeslmao(char **args, char *line)
{
	if (pippin("|", args) == 1)
		pipe_executee(args, line);
	else if (pippin("<", args) == 1)
		sussy(args, line);
	else if (pippin(">", args) == 1)
		right_arrow(args, line, O_WRONLY | O_CREAT | O_TRUNC, ">");
	else if (pippin(">>", args) == 1)
		right_arrow(args, line, O_RDWR | O_CREAT | O_APPEND, ">>");
	else if (pippin("<<", args) == 1)
		amongus(args);
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
