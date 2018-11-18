/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 23:17:55 by ygaude            #+#    #+#             */
/*   Updated: 2018/11/18 01:02:11 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libft.h"
#include "push_swap.h"
#include "visu.h"

static Uint32	getdelay(Uint32 scancode, int *autoplay, Uint32 orig)
{
	Uint32		*vtab;
	int			buf;

	buf = *autoplay;
	vtab = (Uint32[9]){1000, 200, 100, 75, 50, 25, 15, 5, 1};
	*autoplay = 1;
	if (SDL_SCANCODE_KP_1 <= scancode && scancode <= SDL_SCANCODE_KP_9)
		return (vtab[scancode - SDL_SCANCODE_KP_1]);
	if (scancode == SDL_SCANCODE_SPACE)
		return (0);
	*autoplay = buf;
	return (orig);
}

int				events(t_winenv *env)
{
	SDL_Event	event;
	int			cont;

	cont = env->quit;
	while (!cont)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				env->quit |= event.key.keysym.scancode == SDL_SCANCODE_Q;
				if (event.key.keysym.scancode == SDL_SCANCODE_KP_0)
					env->autoplay = 0;
				if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
					cont = 1;
				env->delay = getdelay(event.key.keysym.scancode, &env->autoplay,
																	env->delay);
			}
			env->quit |= event.type == SDL_QUIT;
		}
		cont |= (env->autoplay || env->quit);
	}
	return (!env->quit);
}
