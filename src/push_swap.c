/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:11:47 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/03 20:55:20 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "push_swap.h"
#include "libft.h"

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
	while (bigger - lower != 0 && bigger - lower != -1)
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
	return (cur->last->n);
}

void			doinstruct(char *instruct, t_pile **p1, t_pile **p2)
{
	ft_putendl(instruct);
	apply(instruct, p1, p2);
}

static int		ksorted(t_pile *pile, int apile)
{
	t_pile	*cur;
	int		i;

	i = 0;
	cur = pile;
	while (cur->next != pile && ((apile && cur->n > cur->next->n) ||
								(!apile && cur->n < cur->next->n)))
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

static int		issorted(t_pile *pile, int until, int apile)
{
	return (ksorted(pile, apile) == until);
}

void			sort3(t_pile **p1, t_pile **p2, int until, int apile)
{
	int		a;
	int		b;
	int		c;

	a = (apile) ? (*p1)->n : (*p2)->next->n;
	b = (apile) ? (*p1)->next->n : (*p2)->n;
	if (until == 3 && !issorted((apile) ? *p1 : *p2, 3, apile))
	{
		a = (apile) ? (*p1)->n : (*p2)->next->next->n;
		b = (apile) ? (*p1)->next->n : (*p2)->next->n;
		c = (apile) ? (*p1)->next->next->n : (*p2)->n;
		if ((apile && a < b && b > c) || (!apile && a > b && b < c))
		{
			doinstruct((apile) ? "ra" : "rb", p1, p2);
			doinstruct((apile) ? "sa" : "sb", p1, p2);
			doinstruct((apile) ? "rra" : "rrb", p1, p2);
		}
		else
			doinstruct((apile) ? "sa" : "sb", p1, p2);
		sort3(p1, p2, until, apile);
	}
	else if (until == 2 && a > b)
		doinstruct((apile) ? "sa" : "sb", p1, p2);
}

void			quicksort(t_pile **p1, t_pile **p2, int until, int flag)
{
	int		i;
	int		apile;
	int		reset;
	int		pivot;

	i = 0;
	apile = flag & 1;
	reset = 0;
	pivot = median((apile) ? *p1 : *p2, until);
	if (issorted((apile) ? *p1 : *p2, until, apile))
		return ;
	while (until > 3 && i < (until / 2) + (until % 2 && !apile))
	{
		if ((apile && (*p1)->n < pivot) || (!apile && (*p2)->n >= pivot))
		{
			doinstruct((apile) ? "pb" : "pa", p1, p2);
			i++;
		}
		else
			doinstruct((apile) ? "ra" : "rb" , p1, p2);
		reset++;
	}
	while (!(flag & 0b10) && (reset--) - i)
		doinstruct((apile) ? "rra" : "rrb", p1, p2);
	if (until - i <= 3)
		sort3(p1, p2, until - i, apile);
	else
		quicksort(p1, p2, until - i, apile);
	if (i)
		quicksort(p1, p2, i, !apile | ((flag == 0b11) * 2));
	while (i--)
		doinstruct(apile ? "pa" : "pb", p1, p2);
}

/*
** To do:
** Handle almost sorted list
** optimise quicksort firsts iteration
** add an "instruction pile" to make even more optimisations
*/

static void		makeinstruct(t_pile **p1)
{
	int		k;
	t_pile	*p2;
	t_pile	*cur;

	p2 = NULL;
	cur = *p1;
	k = ksorted(*p1, 1);
	quicksort(p1, &p2, countitem(*p1), 3);
}

int				main(int argc, char **argv)
{
	t_pile	*p1;
	char	*str;
	int		verbose;

	p1 = NULL;
	str = ft_strmerge(argv + 1, 1, argc - 1);
	if (argc <= 1 || parse(str, &p1, &verbose) < 1 || verbose)
		ft_putstr("Error\n");
	else
		makeinstruct(&p1);
	return (0);
}
