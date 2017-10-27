/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 15:33:09 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/27 04:15:54 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

static void		push(t_pile **from, t_pile **to)
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

static void		rotate(t_pile **pile, int reverse)
{
	if (reverse)
		*pile = (*pile)->last;
	else
		*pile = (*pile)->next;
}

static int		apply_s(char *str, t_pile **p1, t_pile **p2)
{
	int		tmp;

	if ((*str == 'a' || *str == 's') && *p1)
	{
		tmp = (*p1)->n;
		(*p1)->n = (*p1)->next->n;
		(*p1)->next->n = tmp;
	}
	if ((*str == 'b' || *str == 's') && *p2)
	{
		tmp = (*p2)->n;
		(*p2)->n = (*p2)->next->n;
		(*p2)->next->n = tmp;
	}
	return ((*str == 'a' || *str == 'b' || *str == 's') && str[1] == '\0');
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

int				apply(char *str, t_pile **p1, t_pile **p2)
{
	if (*str == '\0')
		return (1);
	if (*str == 's')
		return (apply_s(str + 1, p1, p2));
	else if (*str == 'p')
	{
		str++;
		if (*str == 'a')
			push(p2, p1);
		else if (*str == 'b')
			push(p1, p2);
		return (*str == 'a' || *str == 'b');
	}
	else if (*str == 'r')
		return (apply_r(str + 1, p1, p2));
	return (0);
}
