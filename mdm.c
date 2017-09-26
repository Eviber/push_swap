/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mdm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 14:56:03 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/26 18:35:18 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	printtab(int *tab, int size)
{
	int		i;

	i = 0;
	while (i < size)
		printf("%d ", tab[i++]);
	printf("\n");
}

int		ft_isbetween(int a, int b, int c)
{
	return ((a < b && b < c) || (a > b && b > c));
}

int		median(int *tab, int size)
{
	int		i;
	int		j;
	int		bigger;
	int		lower;

	i = 0;
	bigger = 0;
	lower = 10;
	while (bigger - lower != 1 && bigger - lower != 0)
	{
		bigger = 0;
		lower = 0;
		j = -1;
		while (++j < size)
		{
			bigger += (tab[i] < tab[j]);
			lower += (tab[i] > tab[j]);
		}
		i++;
	}
	return (tab[i]);
}

int		main(int argc, char **argv)
{
	int		tab[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
	printf("%zu:%d\n", sizeof(tab) / sizeof(int), median(tab, sizeof(tab) / sizeof(int)));
	return (0);
}
