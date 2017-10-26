/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:51:26 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/26 09:24:54 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "push_swap.h"

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

	if (verbose)
		return (visualize(p));
	count = 0;
	check = 1;
	while (check && get_next_line(0, &str) > 0 && ++count)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		check = apply(str + i, p.p1, p.p2);
		free(str);
	}
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
