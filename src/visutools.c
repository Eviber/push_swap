/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visutools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 23:48:57 by ygaude            #+#    #+#             */
/*   Updated: 2018/11/18 02:50:42 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libft.h"
#include "push_swap.h"
#include "visu.h"

static int		panic(char *str, int ret)
{
	ft_dprintf(2, "Error while %s: %s\n", str, SDL_GetError());
	return (ret);
}

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
		{
			winenv->max = maxvalue(p, &(winenv->pop)) + 1;
			winenv->delay = 100;
			winenv->autoplay = 0;
			winenv->quit = 0;
			winenv->ticks = 0;
			winenv->visuticks = 0;
		}
	return (winenv);
}

int				init(void)
{
	t_winenv	*env;

	env = getsdlenv(NULL);
	if (!env || SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		return (panic("initializing SDL", 1));
	env->win = SDL_CreateWindow("push_swap",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				WIN_W, WIN_H, SDL_WINDOW_RESIZABLE);
	if (!env->win)
		return (panic("creating window", 2));
	env->render = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_ACCELERATED);
	if (!env->render)
		return (panic("creating renderer", 3));
	env->canvas = SDL_CreateTexture(env->render, SDL_PIXELFORMAT_ARGB8888,
							SDL_TEXTUREACCESS_TARGET, WIN_W, env->pop);
	if (!env->canvas)
		return (panic("creating canvas", 4));
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
