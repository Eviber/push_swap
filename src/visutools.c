/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visutools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 23:48:57 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/28 23:56:30 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libft.h"
#include "push_swap.h"
#include "visu.h"

unsigned int	maxvalue(t_pile *p, int *pop)
{
	t_pile			*cur;
	unsigned int	max;

	max = ft_abs(p->n);
	cur = p->next;
	*pop = 1;
	while (cur != p)
	{
		if (ft_abs(cur->n) > max)
			max = ft_abs(cur->n);
		cur = cur->next;
		(*pop)++;
	}
	return (max);
}

t_winenv		*getsdlenv(t_pile *p)
{
	static t_winenv	*winenv = NULL;

	if (!winenv)
		if (p && (winenv = (t_winenv *)malloc(sizeof(t_winenv))))
			winenv->max = maxvalue(p, &(winenv->pop)) + 1;
	return (winenv);
}

int				init(void)
{
	t_winenv	*env;

	env = getsdlenv(NULL);
	if (!env || SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
	{
		fprintf(stderr, "Error while initializing SDL: %s\n", SDL_GetError());
		return (1);
	}
	env->win = SDL_CreateWindow("push_swap",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				WIN_W, WIN_H, 0);
	if (!env->win)
	{
		fprintf(stderr, "Error while creating window: %s\n", SDL_GetError());
		return (2);
	}
	env->render = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_ACCELERATED);
	if (!env->render)
	{
		fprintf(stderr, "Error while creating renderer: %s\n", SDL_GetError());
		return (3);
	}
	SDL_SetRenderDrawColor(env->render, 22, 64, 127, 255);
	SDL_RenderClear(env->render);
	return (0);
}

int				issorted(t_pile *pile)
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
