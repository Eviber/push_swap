/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallsort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 00:06:40 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/26 00:59:31 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	lastend(t_pile *pile)
{
	t_pile	*cur;
	int		last;

	last = pile->last->n;
	cur = pile;
	if (cur->n > last || cur->next->n > last)
		return ((cur->n > last) ? RA : RRA);
	return (0);
}

static void	sort3(t_piles p)
{
	t_pile	*cur;
	char	order;

	cur = *(p.p1);
	if ((order = lastend(cur)))
		doinstruct(order, p.p1, p.p2);
	cur = *(p.p1);
	if (cur->n > cur->next->n)
		doinstruct(SA, p.p1, p.p2);
}

void		smallsort(t_piles p)
{
	sort3(p);
}
