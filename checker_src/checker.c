/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:51:26 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/21 00:22:19 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		split_atoi(char *str, int **p1, size_t *n)
{
	size_t	j;
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			(*p1)[*n] = ft_atoi(str + i);
			while (j < *n)
				if ((*p1)[j++] == (*p1)[*n])
					return (0);
			while (str[i] && ft_isdigit(str[i]))
				i++;
			j = ++(*n);
		}
		else
			i++;
	}
	return (1);
}

static int		checkarg(int argc, char **argv, int **p1, int **p2)
{
	int		a;
	int		n;
	size_t	i;

	n = 0;
	a = 0;
	if (!p1 || !p2)
		return (0);
	while (++a < argc && (i = -1))
		while (argv[a][++i])
		{
			n += ft_isdigit(argv[a][i]) && (!i || ft_isspace(argv[a][i - 1]));
			if (!ft_isdigit(argv[a][i]) && !ft_isspace(argv[a][i]))
				return (-1);
		}
	*p1 = (int *)ft_memalloc(2 * (sizeof(int) * (n + 1)));
	*p2 = *p1 + n + 1;
	a = 0;
	i = 0;
	while (++a < argc)
		if (!split_atoi(argv[a], p1, &i))
			return (-1);
	return(n);
}

int				main(int argc, char **argv)
{
	int		*p1;
	int		*p2;
	int		n;

	if (argc <= 1 || (n = checkarg(argc, argv, &p1, &p2)) == -1)
		ft_putstr("Error\n");
	else
	{
		while (n)
		{
			ft_putnbr(p1[--n]);
			ft_putchar('\n');
		}
	}
	return (0);
}
