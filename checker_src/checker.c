/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:51:26 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/21 22:12:52 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static int		check_n_atoi(char *str, int *n)
{
	int		i;
	int		sign;
	long	tmp;

	i = 0;
	tmp = 0;
	sign = (str[0] == '-') ? -1 : 1;
	i += (str[0] == '-' || str[0] == '+');
	while (ft_isdigit(str[i]))
	{
		tmp = tmp * 10 + (sign * (str[i++] - '0'));
		if (tmp < INT_MIN || tmp > INT_MAX)
			return (0);
	}
	*n = (int)tmp;
	return (1);
}

static int		split_atoi(char *str, int **p1, size_t *n)
{
	size_t	j;
	int		i;
	int		check;

	i = 0;
	check = 1;
	while (check && str[i])
	{
		if (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '+')
		{
			j = 0;
			check = check && check_n_atoi(str + i, &((*p1)[*n]));
			i += (str[i] == '-' || str[i] == '+');
			while (check && j < *n)
				check = check && !((*p1)[j++] == (*p1)[*n]);
			while (check && str[i] && ft_isdigit(str[i]))
				i++;
			(*n)++;
		}
		else
			i++;
	}
	return (check);
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
			n += ft_isdigit(argv[a][i]) && (!i || ft_isspace(argv[a][i - 1]) ||
				argv[a][i - 1] == '-' || argv[a][i - 1] == '+');
			if ((!ft_isdigit(argv[a][i]) && !ft_isspace(argv[a][i])) &&
				!(ft_strchr("+-", argv[a][i]) && ft_isdigit(argv[a][i + 1]) &&
				!ft_isdigit(argv[a][i - 1])))
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

static int		apply_s(char *str, int *p1, int *p2, int len)
{
	if (*str = 'a' || *str 's')
	if (*str = 'b' || *str 's')
}

static int		apply_p(char *str, int *p1, int *p2, int len)
{
	if (*str = 'a' || *str 's')
	if (*str = 'b' || *str 's')
}

static int		apply_r(char *str, int *p1, int *p2, int len)
{
	if (*str = 'a' || *str 's')
	if (*str = 'b' || *str 's')
}

static int		checkinstruct(int *p1, int *p2, int len)
{
	int		i;
	int		check;
	char	*str;

	check = 1;
	while (check && get_next_line(1, &str) > 0)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == 's')
			check = apply_s(str + i + 1, p1, p2, len);
		else if (str[i] == 'p')
			check = apply_p(str + i + 1, p1, p2, len);
		else if (str[i] == 'r')
			check = apply_r(str + i + 1, p1, p2, len);
		else
			check = 0;
	}
	return (1);
}

int				main(int argc, char **argv)
{
	int		*p1;
	int		*p2;
	int		n;

	if (argc <= 1 || (n = checkarg(argc, argv, &p1, &p2)) == -1 ||
		!checkinstruct(p1, p2, n))
		ft_putstr("Error\n");
	else
	{
		while (n)
		{
			ft_putnbr(p1[--n]);
			ft_putchar(' ');
		}
	}
	return (0);
}
