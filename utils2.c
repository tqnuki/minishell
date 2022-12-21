/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:29:22 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/21 16:17:59 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_s;

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

void	prepend(char *s, const char *t)
{
	size_t	len;

	len = ft_strlen(t);
	ft_memmove(s + len, s, ft_strlen(s) + 1);
	ft_memcpy(s, t, len);
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
			break ;
		}
	ptr++;
	}
}

void sus(char *str)
{
    size_t i;
    size_t len;

    len = ft_strlen(str);
    if (len > 2)
    {
        for (i = 1; i < len - 1; i++)
        {
            printf("%c", str[i]);
        }
    }
    else
    {
        printf("%s", str);
    }
}

void	goofyahh2(char **args, int i, char *str)
{
	int	l;
	size_t	k;
	int q;
	int sq;

	q = 0;
	sq = 0;
	k = 0;
	l = 0;
	if (args[i][0] == '"')
		q = 1;
	if (args[i][0] == '\'')
		sq = 1;
	while (args[i])
	{
		if (isdollar(args[i]) && !sq)
		{
			if(q)
				k++;
			if (ft_strcmp((args[i]), "$?") == 0)
				printf("%d", g_s->thing);
			else
			{
				while (args[i][k] && args[i][k] != '$')
					printf("%c", args[i][k++]);
				k++;
				while (args[i][k] && ft_isalnum(args[i][k]))
				{
					if(q && k == ft_strlen(args[i]) - 1)
						break;
					str[l++] = args[i][k++];
				}
				printf("%s", get_value(g_s->env, str));
			}
		}
		else
		{
			if(sq || q)
				sus(args[i]);
			else
				printf("%s", args[i]);
		}
		if (args[i +1])
			printf(" ");
		i++;
	}
}

void	mini_unset(char *str)
{
	int	i;
	int	boul;

	i = -1;
	boul = 0;
	while (g_s->env[++i])
		if (ft_strncmp(g_s->env[i], str, ft_strlen(str)) == 0)
		{
			boul = 1;
			break ;
		}
	if (boul == 1)
	{
		while (g_s->env[i + 1])
		{
			g_s->env[i] = g_s->env[i + 1];
			i++;
		}
		g_s->env[i] = NULL;
	}
}
