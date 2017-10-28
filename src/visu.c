/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 06:57:16 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/28 04:08:04 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libft.h"
#include "push_swap.h"

# define WIN_W 1920
# define WIN_H 1000

typedef struct			s_winenv
{
	SDL_Rect			dst;
	SDL_Rect			src;
	SDL_Texture			*tex;
	SDL_Window			*win;
	SDL_Renderer		*render;
}						t_winenv;

t_winenv				*getsdlenv(void)
{
	static t_winenv	*winenv = NULL;

	if (!winenv)
		winenv = (t_winenv *)malloc(sizeof(t_winenv));
	return (winenv);
}

int				init(void)
{
	t_winenv	*env;

	env = getsdlenv();
	if(!env || SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
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

unsigned int	ft_abs(int n)
{
	return ((unsigned int)((n < 0) ? -n : n));
}

static unsigned int	maxvalue(t_pile *p, int *pop)
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

static void		displaypile(t_winenv *env, t_pile *p, SDL_Rect rect, unsigned int max, int pop)
{
	t_pile			*cur;
	int				orix;

	if (!p)
		return ;
	orix = rect.x;
	cur = p->last;
	rect.h = WIN_H / pop;
	while (cur && cur != p)
	{
		rect.y -= rect.h;
		rect.w = WIN_W / 2 * (ft_abs(cur->n) + 1) / max;
		rect.x = orix - (rect.w / 2);
		if (cur->n < 0)
			SDL_SetRenderDrawColor(env->render, 255, 255, 255, 0);
		else
			SDL_SetRenderDrawColor(env->render, 0, 0, 0, 0);
		SDL_RenderFillRect(env->render, &rect);
		cur = cur->last;
	}
	rect.w = WIN_W / 2 * (ft_abs(cur->n) + 1) / max;
	rect.x = orix - (rect.w / 2);
	if (cur->n < 0)
		SDL_SetRenderDrawColor(env->render, 255, 255, 255, 0);
	else
		SDL_SetRenderDrawColor(env->render, 0, 0, 0, 0);
	SDL_RenderFillRect(env->render, &rect);
}

static void		displaystatus(t_piles p, unsigned int max, int pop)
{
	t_winenv 	*env;
	SDL_Rect	rect;

	env = getsdlenv();
	clear(env);
	rect.w = 1;
	rect.h = 1;
	rect.y = WIN_H - rect.h;
	rect.x = WIN_W / 4;
	displaypile(env, *(p.p1), rect, max, pop);
	rect.x = 3 * WIN_W / 4;
	displaypile(env, *(p.p2), rect, max, pop);
	SDL_RenderPresent(env->render);
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
/*
void			navigate(t_piles p, t_order map)
{
	Uint8	*keys;
	t_order	*cur;
	int		autoplay;
	Uint8	spaced;

	autoplay = 0;
	spaced = 0;
	cur = map.last;
	keys = (Uint8 *)SDL_GetKeyboardState(NULL);
	while (!SDL_QuitRequested())
	{
		SDL_PumpEvents();
		autoplay = (keys[SDL_SCANCODE_SPACE] && !spaced) ? !autoplay : autoplay;
		if ((keys[SDL_SCANCODE_LEFT] && cur->last) || (cur->next && (keys[SDL_SCANCODE_RIGHT] || autoplay)))
		{
			ft_printf("%s", strinstruct((keys[SDL_SCANCODE_LEFT]) ? opposite(cur->order) : cur->order));
			apply(strinstruct((keys[SDL_SCANCODE_LEFT]) ? opposite(cur->order) : cur->order), p.p1, p.p2);
			displaystatus(p);
			if (keys[SDL_SCANCODE_LEFT] && cur->last)
				cur = cur->last;
			else if (cur->next)
				cur = cur->next;
			SDL_Delay(1000/60);
		}
		spaced = keys[SDL_SCANCODE_SPACE];
	}
}
*/
int				visualize(t_piles p)
{
	char			*str;
	unsigned int	count;
	unsigned int	max;
	int				pop;
	int				i;
	int				check;

	max = maxvalue(*(p.p1), &pop);
	ft_printf("max = %u ; pop = %d\n", max, pop);
	count = 0;
	check = 1;
	if (init())
		return (0);
	displaystatus(p, max, pop);
	while (!SDL_QuitRequested() && check && get_next_line(0, &str) > 0 && ++count)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		check = apply(str + i, p.p1, p.p2);
		displaystatus(p, max, pop);
		SDL_Delay(WIN_H / pop);
		free(str);
	}
	while (!SDL_QuitRequested())
		;
	return ((!check) ? -1 : (*p.p2 == NULL && issorted(*p.p1)));
}
