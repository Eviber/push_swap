/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:24:12 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/26 04:43:47 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void		doinstruct(char instruct, t_pile **p1, t_pile **p2)
{
	t_todo	**list;

	list = getlist();
	addorder(list, instruct);
	apply(strinstruct(instruct), p1, p2);
}

char		*strinstruct(char n)
{
	if (n == PA)
		return ("pa\n");
	else if (n == PB)
		return ("pb\n");
	else if (n == SA)
		return ("sa\n");
	else if (n == SB)
		return ("sb\n");
	else if (n == SS)
		return ("ss\n");
	else if (n == RA)
		return ("ra\n");
	else if (n == RB)
		return ("rb\n");
	else if (n == RR)
		return ("rr\n");
	else if (n == RRA)
		return ("rra\n");
	else if (n == RRB)
		return ("rrb\n");
	else if (n == RRR)
		return ("rrr\n");
	else
		return ("ERROR\n");
}

static int	tobedel(t_todo *list)
{
	char	order;

	if (!list || !list->next)
		return (0);
	order = list->order;
	while (list->next && !isblocking(order, list->next->order))
	{
		if (isopposed(order, list->next->order))
		{
			delnext(list);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int			del(t_todo **list)
{
	t_todo	*cur;
	int		ret;

	ret = 0;
	if (!list)
		return (ret);
	cur = *list;
	while (tobedel(*list))
	{
		ret = 1;
		cur = (*list)->next;
		free(*list);
		*list = cur;
	}
	while (cur && cur->next)
	{
		if (tobedel(cur->next))
		{
			ret = 1;
			delnext(cur);
		}
		cur = cur->next;
	}
	return (ret);
}

void		printinstruct(void)
{
	t_todo	**list;
	t_todo	*cur;
	char	buffer[2048];
	char	*str;
	int		i;

	list = getlist();
	cur = *list;
	i = 0;
	while (cur)
	{
		if (i > 2043)
		{
			ft_putstr(buffer);
			i = 0;
		}
		str = strinstruct(cur->order);
		ft_strcpy(buffer + i, str);
		i += ft_strlen(str);
		cur = cur->next;
	}
	ft_putstr(buffer);
}
