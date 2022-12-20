/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:15:03 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/20 09:17:50 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pippin(char *str, char **av)
{
	int	i;

	i = -1;
	while (av[++i])
		if (av[i][0] == str[0] && av[i][1] == '\0' && str[1] == '\0')
			return (1);
	return (0);
}

void	trim(char **av)
{
	int	i;

	i = -1;
	while (av[++i])
		av[i] = ft_strtrim(av[i], " ");
}

char	**cupid(char *str)
{
	char	**rep;

	rep = malloc(sizeof(char *) * 2);
	rep[0] = ft_strdup(str);
	rep[1] = NULL;
	return (rep);
}
