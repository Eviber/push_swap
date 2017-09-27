/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:11:47 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/27 14:54:39 by ygaude           ###   ########.fr       */
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

void			doinstruct(char *instruct, t_pile **p1, t_pile **p2)
{
	ft_putendl(instruct);
	apply(instruct, p1, p2);
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
