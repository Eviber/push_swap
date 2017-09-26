/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:51:26 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/26 21:10:29 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "push_swap.h"

#           include <stdio.h>
static void		putpiles(t_pile *p1, t_pile *p2)
{
	t_pile	*cur;
	int		len1;
	int		len2;

	len1 = (p1  != NULL);
	cur = p1;
	while (cur && cur->next != p1 && len1++)
		cur = cur->next;
	len2 = (p2  != NULL);
	cur = p2;
	while (cur && cur->next != p2 && len2++)
		cur = cur->next;
	while (len1 || len2)
	{
		printf("\t\t%-11.*d|%11.*d\n", (len1 >= len2), p1->n * (len1 >= len2),
				(len1 <= len2), p2->n * (len1 <= len2));
		p1 = (len1 >= len2) ? p1->next : p1;
		p2 = (len2 >= len1) ? p2->next : p2;
		len1 -= (len1 >= len2);
		len2 -= (len2 > len1);
	}
	printf("\t\t-----------------------\n\t\ta%10.0d %10.0db\n\n\n", 0, 0);
}

static int		issorted(t_pile *pile)
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

static int		checkinstruct(t_pile **p1, int verbose)
{
	t_pile	*p2;
	int		i;
	int		check;
	char	*str;

	p2 = NULL;
	check = 1;
	if (verbose)
		putpiles(*p1, p2);
	while (check && get_next_line(0, &str) > 0)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		apply(str + i, p1, &p2);
		free(str);
		if (verbose)
			putpiles(*p1, p2);
	}
	return ((!check) ? -1 : (p2 == NULL && issorted(*p1)));
}

int				main(int argc, char **argv)
{
	t_pile	*p1;
	char	*str;
	int		ret;
	int		verbose;

	p1 = NULL;
	str = ft_strmerge(argv + 1, 1, argc - 1);
	if (argc <= 1 || parse(str, &p1, &verbose) < 1 ||
		(ret = checkinstruct(&p1, verbose)) == -1)
		ft_putstr("Error\n");
	else if (ret)
		ft_putstr("OK\n");
	else
		ft_putstr("KO\n");
	free(str);
	return (0);
}
