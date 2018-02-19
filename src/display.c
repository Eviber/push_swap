/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 23:26:38 by ygaude            #+#    #+#             */
/*   Updated: 2018/02/19 23:27:08 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libft.h"
#include "push_swap.h"
#include "visu.h"

static void		clear(t_winenv *env)
{
	SDL_Rect	rect;

	rect.w = WIN_W / 2;
	rect.h = env->pop;
	rect.x = 0;
	rect.y = 0;
	SDL_SetRenderDrawColor(env->render, 17, 72, 122, 0);
	SDL_RenderFillRect(env->render, &rect);
	rect.x = rect.w;
	SDL_SetRenderDrawColor(env->render, 35, 100, 148, 0);
	SDL_RenderFillRect(env->render, &rect);
}

static void		displayunit(SDL_Renderer *render, int n, SDL_Rect rect)
{
	if (n > 0)
		SDL_SetRenderDrawColor(render, 90, 147, 199, 0);
	else if (n < 0)
		SDL_SetRenderDrawColor(render, 175, 204, 225, 0);
	else
		SDL_SetRenderDrawColor(render, 212, 241, 255, 0);
	SDL_RenderFillRect(render, &rect);
}

static void		displaypile(t_winenv *env, t_pile *p, SDL_Rect rect)
{
	t_pile			*cur;
	int				orix;

	if (!p)
		return ;
	orix = rect.x;
	cur = p->last;
	while (cur && cur != p)
	{
		rect.y -= rect.h;
		rect.w = WIN_W / 2 * (ft_abs(cur->n) + 1) / env->max;
		rect.x = orix - (rect.w / 2);
		displayunit(env->render, cur->n, rect);
		cur = cur->last;
	}
	rect.y -= rect.h;
	rect.w = WIN_W / 2 * (ft_abs(cur->n) + 1) / env->max;
	rect.x = orix - (rect.w / 2);
	displayunit(env->render, cur->n, rect);
	SDL_RenderFillRect(env->render, &rect);
}

void			displaystatus(t_piles p)
{
	t_winenv	*env;
	SDL_Rect	rect;

	env = getsdlenv(NULL);
	SDL_SetRenderTarget(env->render, env->canvas);
	clear(env);
	rect.h = 1;
	rect.y = env->pop;
	rect.x = WIN_W / 4;
	displaypile(env, *(p.p1), rect);
	rect.x += WIN_W / 2;
	displaypile(env, *(p.p2), rect);
	SDL_SetRenderTarget(env->render, NULL);
	SDL_RenderCopy(env->render, env->canvas, NULL, NULL);
	SDL_RenderPresent(env->render);
}
