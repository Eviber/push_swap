/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:11:47 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/29 19:04:49 by ygaude           ###   ########.fr       */
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

int				ksorted(t_pile *pile, int apile)
{
	t_pile	*cur;
	int		i;

	i = 1;
	cur = pile;
	while (cur->next != pile && ((apile && cur->n < cur->next->n) ||
								(!apile && cur->n > cur->next->n)))
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

static int		issorted(t_pile *pile, int until, int apile)
{
	return (ksorted(pile, apile) >= until);
}

static void		makeinstruct(t_pile **p1)
{
	t_piles	p;
	t_pile	*p2;
	t_todo	**list;
	int		size;

	p2 = NULL;
	p.p1 = p1;
	p.p2 = &p2;
	size = countitem(*(p.p1));
	if (!issorted(*(p.p1), size, 1))
	{
		if (size <= 3)
			smallsort(p);
		else
			quicksort(p, size, 1, 1);
		list = getlist();
		while (del(list))
			;
		printinstruct();
	}
}

int				main(int argc, char **argv)
{
	t_pile	*p1;
	char	*str;
	int		verbose;

	p1 = NULL;
	str = ft_strmerge(argv + 1, 1, argc - 1);
	if (!(parse(str, &p1, &verbose) < 1 || verbose))
		makeinstruct(&p1);
	else if (argc > 1)
		ft_putstr("Error\n");
	ft_strdel(&str);
	return (0);
}
