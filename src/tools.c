/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 22:15:47 by ygaude            #+#    #+#             */
/*   Updated: 2018/11/18 18:16:14 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

t_todo		**getlist(void)
{
	static t_todo	*list = NULL;

	return (&list);
}

char		invert(char order)
{
	int		res;

	res = 0;
	while (!isopposed(order, res))
		res++;
	return (res);
}

void		addorder(t_todo **todo, char order)
{
	t_todo	*new;
	t_todo	*cur;

	if (todo && (new = (t_todo *)malloc(sizeof(t_todo))))
	{
		new->next = NULL;
		new->prec = NULL;
		new->order = order;
		new->invert = invert(order);
		cur = *todo;
		if (!cur)
			*todo = new;
		else
		{
			while (cur->next)
				cur = cur->next;
			new->prec = cur;
			cur->next = new;
		}
	}
}

void		delnext(t_todo *ptr)
{
	t_todo	*tmp;

	if (ptr && ptr->next)
	{
		tmp = ptr->next->next;
		free(ptr->next);
		ptr->next = tmp;
	}
}

int			isblocking(char order1, char order2)
{
	char	tmp;

	if (order1 > order2)
	{
		tmp = order1;
		order1 = order2;
		order2 = tmp;
	}
	if (order1 <= PB && (order2 > PB || order2 == order1))
		return (1);
	else if (order1 == SA && (order2 == RA || order2 == RRA))
		return (1);
	else if (order1 == SB && (order2 == RB || order2 == RRB))
		return (1);
	return (0);
}

int			isopposed(char order1, char order2)
{
	char	tmp;

	if (order1 > order2)
	{
		tmp = order1;
		order1 = order2;
		order2 = tmp;
	}
	if (order1 <= PB && order2 <= PB)
		return (order1 != order2);
	else if (order1 <= SB && order2 == order1)
		return (1);
	else if ((order1 == RA && order2 == RRA) || (order1 == RB && order2 == RRB))
		return (1);
	return (0);
}
