/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 06:57:16 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/28 23:52:50 by ygaude           ###   ########.fr       */
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
	rect.h = WIN_H;
	rect.x = 0;
	rect.y = 0;
	SDL_SetRenderDrawColor(env->render, 150, 150, 200, 0);
	SDL_RenderFillRect(env->render, &rect);
	rect.x = WIN_W / 2;
	SDL_SetRenderDrawColor(env->render, 200, 150, 150, 0);
	SDL_RenderFillRect(env->render, &rect);
}

static void		displayunit(SDL_Renderer *render, int n, SDL_Rect rect)
{
	if (n < 0)
		SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
	else if (n > 0)
		SDL_SetRenderDrawColor(render, 50, 50, 50, 0);
	else
		SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
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
	rect.h = WIN_H / env->pop;
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

static void		displaystatus(t_piles p)
{
	t_winenv	*env;
	SDL_Rect	rect;

	env = getsdlenv(NULL);
	clear(env);
	rect.w = 1;
	rect.h = 1;
	rect.y = WIN_H - rect.h;
	rect.x = WIN_W / 4;
	displaypile(env, *(p.p1), rect);
	rect.x = 3 * WIN_W / 4;
	displaypile(env, *(p.p2), rect);
	SDL_RenderPresent(env->render);
}

int				visualize(t_piles p)
{
	char			*str;
	int				i;
	int				check;

	check = 1;
	getsdlenv(*(p.p1));
	if (init())
		return (0);
	displaystatus(p);
	while (!SDL_QuitRequested() && check && get_next_line(0, &str) > 0)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		check = apply(str + i, p.p1, p.p2);
		displaystatus(p);
		SDL_Delay(WIN_H / (getsdlenv(NULL)->pop));
		free(str);
	}
	while (!SDL_QuitRequested())
		;
	return ((!check) ? -1 : (*p.p2 == NULL && issorted(*p.p1)));
}
