/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 05:49:56 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/15 02:28:55 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "push_swap.h"
#include "libft.h"

static int		issorted(t_pile *pile, int until, int apile)
{
	return (ksorted(pile, apile) >= until);
}

int				median(t_pile *pile, int size)
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
			doinstruct((apile) ? RA : RB, p1, p2);
			doinstruct((apile) ? SA : SB, p1, p2);
			doinstruct((apile) ? RRA : RRB, p1, p2);
		}
		else
			doinstruct((apile) ? SA : SB, p1, p2);
		sort3(p1, p2, until, apile);
	}
	else if (until == 2 && a > b)
		doinstruct((apile) ? SA : SB, p1, p2);
}

int				act(t_pile **p1, t_pile **p2, int apile, int pivot)
{
	if ((apile && (*p1)->n < pivot) || (!apile && (*p2)->n >= pivot))
	{
		doinstruct((apile) ? PB : PA, p1, p2);
		return (1);
	}
	else
		doinstruct((apile) ? RA : RB, p1, p2);
	return (0);
}

void			quicksort(t_piles p, int until, int apile, int fiter)
{
	int		i;
	int		reset;
	int		pivot;

	i = 0;
	reset = 0;
	pivot = median((apile) ? *(p.p1) : *(p.p2), until);
	if (issorted((apile) ? *(p.p1) : *(p.p2), until, apile))
		return ;
	while (until > 3 && i < (until / 2) + (until % 2 && !apile) && ++reset)
		i += act(p.p1, p.p2, apile, pivot);
	while ((!fiter) && (reset--) - i)
		doinstruct((apile) ? RRA : RRB, p.p1, p.p2);
	if (i && !apile)
		quicksort(p, i, !apile, 0);
	if (until - i <= 3)
		sort3(p.p1, p.p2, until - i, apile);
	else
		quicksort(p, until - i, apile, (fiter == 2) ? fiter - 1 : fiter);
	if (i && apile)
		quicksort(p, i, !apile, (fiter == 2) ? 1 : 0);
	while (i--)
		doinstruct(apile ? PA : PB, p.p1, p.p2);
}
