/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpankewi <mpankewi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:29:53 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/23 12:05:29 by mpankewi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_s;

void	pipeslmao(char **args, char *line)
{
	if (pippin("|", args) == 1)
		pipe_execute(args, line);
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

void	goofyahhfunction(char **args, int i, char *str)
{
	if (isdollar(args[i]) && !g_s->sq)
	{
		amongusahh(args, str, i);
	}
	else
	{
		if (g_s->sq || g_s-> q)
			sus(args[i]);
		else
			printf("%s", args[i]);
	}
}

void	sus(char *str)
{
	size_t	i;
	size_t	len;

	i = 1;
	len = ft_strlen(str);
	if (len > 2)
	{
		while (i < len - 1)
		{
			printf("%c", str[i++]);
		}
	}
	else
	{
		printf("%s", str);
	}
}
