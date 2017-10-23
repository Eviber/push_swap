/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:24:12 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/23 20:43:45 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

static t_todo		**getlist(void)
{
	static t_todo	*list = NULL;

	return (&list);
}

void				addorder(t_todo **todo, char order)
{
	t_todo	*new;
	t_todo	*cur;

	if (todo && (new = (t_todo *)malloc(sizeof(t_todo))))
	{
		new->next = NULL;
		new->order = order;
		cur = *todo;
		if (!cur)
			*todo = new;
		else
		{
			while (cur->next)
				cur = cur->next;
			cur->next = new;
		}
	}
}

static char			*strinstruct(char n)
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

void				doinstruct(char instruct, t_pile **p1, t_pile **p2)
{
	t_todo	**list;

	list = getlist();
	addorder(list, instruct);
	apply(strinstruct(instruct), p1, p2);
}

void				cleaninstruct(void)
{
	t_todo	**list;

	list = getlist();
}

void				printinstruct(void)
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
