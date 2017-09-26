/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 17:15:22 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/24 18:34:24 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#include "push_swap.h"

static void		add(t_pile **pile, int n)
{
	t_pile	*tmp;

	if (!pile || !(tmp = (t_pile *)malloc(sizeof(t_pile))))
		return ;
	tmp->n = n;
	if (!*pile)
	{
		*pile = tmp;
		tmp->next = tmp;
		tmp->last = tmp;
	}
	else
	{
		tmp->next = *pile;
		tmp->last = (*pile)->last;
		(*pile)->last->next = tmp;
		(*pile)->last = tmp;
	}
}

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

static int		split_atoi(char *str, t_pile **p1)
{
	t_pile	*cur;
	int		tmp;
	int		i;
	int		check;

	i = 0;
	check = 1;
	while (check && str[i])
	{
		if (ft_strchr("0123456789-+", str[i]) && str[i + 1] != 'v')
		{
			check = check && check_n_atoi(str + i, &tmp);
			add(p1, tmp);
			cur = *p1;
			while (check && cur != (*p1)->last)
			{
				check = check && !(cur->n == (*p1)->last->n);
				cur = cur->next;
			}
			i += (str[i] == '-' || str[i] == '+');
			while (check && str[i] && ft_isdigit(str[i]))
				i++;
		}
		else
			i++;
	}
	return (check);
}

int				parse(char *str, t_pile **p1, int *verbose)
{
	size_t	i;

	*verbose = -1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	*verbose = (str[i] == '-' && str[i + 1] == 'v' && !ft_isdigit(str[i + 2]));
	i += *verbose * 2;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]) && !(ft_strchr("+-",
				str[i]) && ft_isdigit(str[i + 1]) && !ft_isdigit(str[i - 1])))
			return (-1);
		i++;
	}
	if (!split_atoi(str, p1))
		return (-1);
	return(*p1 != NULL);
}
