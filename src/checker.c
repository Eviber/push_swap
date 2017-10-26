/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:51:26 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/26 04:13:29 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "push_swap.h"

static void		putpiles(t_pile *p1, t_pile *p2)
{
	t_pile	*cur;
	int		len1;
	int		len2;

	len1 = (p1 != NULL);
	cur = p1;
	while (cur && cur->next != p1 && len1++)
		cur = cur->next;
	len2 = (p2 != NULL);
	cur = p2;
	while (cur && cur->next != p2 && len2++)
		cur = cur->next;
	while (len1 || len2)
	{
		ft_printf("\n%-11.*d|%11.*d", (len1 >= len2),
		(len1 >= len2) ? p1->n : 0, (len1 <= len2), (len1 <= len2) ? p2->n : 0);
		p1 = (len1 >= len2) ? p1->next : p1;
		p2 = (len2 >= len1) ? p2->next : p2;
		len1 -= (len1 >= len2);
		len2 -= (len2 > len1);
	}
	ft_printf("\n-----------------------\na%10.0d %10.0db\n\n\n", 0, 0);
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

static int		checkinstruct(t_piles p, int verbose)
{
	int				i;
	unsigned int	count;
	int				check;
	char			*str;

	count = 0;
	check = 1;
	if (verbose)
		putpiles(*(p.p1), *(p.p2));
	while (check && get_next_line(0, &str) > 0 && ++count)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		check = apply(str + i, p.p1, p.p2);
		if (verbose)
		{
			ft_putendl(str);
			putpiles(*p.p1, *p.p2);
		}
		free(str);
	}
	if (verbose)
		ft_printf("%u instructions\n", count);
	return ((!check) ? -1 : (*p.p2 == NULL && issorted(*p.p1)));
}

int				main(int argc, char **argv)
{
	t_piles	p;
	char	*str;
	int		ret;
	int		verbose;

	p.p1 = (t_pile **)malloc(sizeof(t_pile *));
	p.p2 = (t_pile **)malloc(sizeof(t_pile *));
	*(p.p1) = NULL;
	*(p.p2) = NULL;
	str = ft_strmerge(argv + 1, 1, argc - 1);
	if (argc > 1 && (parse(str, p.p1, &verbose) < 1 ||
		(ret = checkinstruct(p, verbose)) == -1))
		ft_putstr("Error\n");
	else if (argc > 1 && ret)
		ft_putstr("OK\n");
	else if (argc > 1)
		ft_putstr("KO\n");
	free(str);
	return (0);
}
