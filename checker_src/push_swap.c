/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:11:47 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/26 18:52:03 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

typedef struct		s_pile
{
	struct s_pile	*next;
	struct s_pile	*last;
	int				n;
}					t_pile;

void			add(t_pile **pile, int n)
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

static int		checkarg(char *str, t_pile **p1, int *verbose)
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
		if (*verbose != -1 && (!ft_isdigit(str[i]) &&
			!ft_isspace(str[i])) && !(ft_strchr("+-", str[i]) &&
			ft_isdigit(str[i + 1]) && !ft_isdigit(str[i - 1])))
				return (-1);
		i++;
	}
	if (!split_atoi(str, p1))
		return (-1);
	return(*p1 != NULL);
}

void			swap(t_pile *pile)
{
	int		tmp;

	tmp = pile->n;
	pile->n = pile->next->n;
	pile->next->n = tmp;
}

void			push(t_pile **from, t_pile **to)
{
	t_pile	*tmp;

	if (*from)
	{
		tmp = *from;
		tmp->last->next = tmp->next;
		tmp->next->last = tmp->last;
		*from = (tmp != tmp->next) ? tmp->next : NULL;
		tmp->next = (*to) ? *to : tmp;
		tmp->last = (*to) ? (*to)->last : tmp;
		if (*to)
		{
			(*to)->last->next = tmp;
			(*to)->last = tmp;
		}
		*to = tmp;
	}
}

void			rotate(t_pile **pile, int reverse)
{
	if (reverse)
		*pile = (*pile)->last;
	else
		*pile = (*pile)->next;
}

static int		apply_s(char *str, t_pile **p1, t_pile **p2)
{
	if ((*str == 'a' || *str == 's') && *p1)
		swap(*p1);
	if ((*str == 'b' || *str == 's') && *p2)
		swap(*p2);
	return ((*str == 'a' || *str == 'b' || *str == 's') && str[1] == '\0');
}

static int		apply_p(char *str, t_pile **p1, t_pile **p2)
{
	if (*str == 'a')
		push(p2, p1);
	else if (*str == 'b')
		push(p1, p2);
	return ((*str == 'a' || *str == 'b') && str[1] == '\0');
}

static int		apply_r(char *str, t_pile **p1, t_pile **p2)
{
	int		reverse;

	reverse = (str[0] == 'r' && str[1]);
	str += reverse;
	if ((*str == 'a' || *str == 'r') && *p1)
		rotate(p1, reverse);
	if ((*str == 'b' || *str == 'r') && *p2)
		rotate(p2, reverse);
	return ((*str == 'a' || *str == 'b' || *str == 'r') && str[1] == '\0');
}

int				issorted(t_pile *pile)
{
	t_pile	*cur;
	int		sorted;

	cur = pile;
	sorted = 1;
	while (sorted && cur->next != pile)
	{
		if (cur->n >= cur->next->n)
			sorted = 0;
		cur = cur->next;
	}
	return (sorted);
}

int				countitem(t_pile *pile)
{
	int		res;
	t_pile	*cur;

	res = 0;
	cur = pile;
	while (pile && ++res && cur->next != pile)
		cur = cur->next;
	return (res);
}

int				getmedian(t_pile *pile, int size)
{
	int		res;
	int		ratio;
	t_pile	*cur;

	res = pile->n;
	cur = pile;
	ratio = 0;
	while (cur->next != pile)
	{
		cur = cur->next;
		ratio += (cur->n < res) ? -1 : 1;
		if (ratio < -1 || ratio > 1)
		{
			ratio += (ratio < -1) ? 1 : -1;
		}
	}
}

int		median(t_pile *pile, int size)
{
	int		bigger;
	int		lower;
	int		i;
	t_pile	*cur;
	t_pile	*tmp;

	cur = pile;
	bigger = 0;
	lower = 10;
	while (bigger - lower != 1 && bigger - lower != 0)
	{
		bigger = 0;
		lower = 0;
		i = -1;
		tmp = pile;
		while (++i < size)
		{
			bigger += (cur->n < tmp->n);
			lower += (cur->n > tmp->n);
			tmp = tmp->next;
		}
		cur = cur->next;
	}
	return (cur->n);
}

void			quicksort(t_pile **src, t_pile **dst, int until)
{

}

static void		makeinstruct(t_pile **p1)
{
	t_pile	*p2;
	int		i;
	int		check;
	char	*str;

	p2 = NULL;
	quicksort(p1, &p2, countitem(*p1));
}

int				main(int argc, char **argv)
{
	t_pile	*p1;
	char	*str;
	int		ret;
	int		verbose;

	p1 = NULL;
	str = ft_strmerge(argv + 1, 1, argc - 1);
	if (argc <= 1 || checkarg(str, &p1, &verbose) < 1)
		ft_putstr("Error\n");
	makeinstruct(&p1);
	return (0);
}
