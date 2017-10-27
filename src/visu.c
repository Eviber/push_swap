/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 06:57:16 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/27 04:39:14 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libft.h"
#include "push_swap.h"

# define WIN_W 1920
# define WIN_H 1080

typedef struct			s_winenv
{
	SDL_Rect			dst;
	SDL_Rect			src;
	SDL_Texture			*tex;
	SDL_Window			*win;
	SDL_Renderer		*render;
}						t_winenv;

typedef struct			s_order
{
	struct s_order		*next;
	struct s_order		*last;
	char				order;
}						t_order;

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

static void		displaypile(t_winenv *env, t_pile *p, SDL_Rect rect)
{
	t_pile			*cur;

	if (!p)
		return ;
	cur = p->last;
	while (cur && cur != p)
	{
		rect.w = 10 * cur->n;
		if (cur->n < 0)
			SDL_SetRenderDrawColor(env->render, 255, 255, 255, 0);
		else
			SDL_SetRenderDrawColor(env->render, 0, 0, 0, 0);
		SDL_RenderFillRect(env->render, &rect);
		cur = cur->last;
		rect.y -= rect.h;
	}
	rect.w = 10 * cur->n;
	if (cur->n < 0)
		SDL_SetRenderDrawColor(env->render, 255, 255, 255, 0);
	else
		SDL_SetRenderDrawColor(env->render, 0, 0, 0, 0);
	SDL_RenderFillRect(env->render, &rect);
}

static void		displaystatus(t_piles p)
{
	t_winenv 	*env;
	SDL_Rect	rect;

	env = getsdlenv();
	clear(env);
	rect.w = 10;
	rect.h = 10;
	rect.y = WIN_H - rect.h;
	rect.x = WIN_W / 4;
	displaypile(env, *(p.p1), rect);
	rect.x = 3 * WIN_W / 4;
	displaypile(env, *(p.p2), rect);
	SDL_RenderPresent(env->render);
}

static char		strton(char *str)
{
	if (ft_strequ(str, "pa"))
		return (PA);
	if (ft_strequ(str, "pb"))
		return (PB);
	if (ft_strequ(str, "sa"))
		return (SA);
	if (ft_strequ(str, "sb"))
		return (SB);
	if (ft_strequ(str, "ss"))
		return (SS);
	if (ft_strequ(str, "ra"))
		return (RA);
	if (ft_strequ(str, "rb"))
		return (RB);
	if (ft_strequ(str, "rr"))
		return (RR);
	if (ft_strequ(str, "rra"))
		return (RRA);
	if (ft_strequ(str, "rrb"))
		return (RRB);
	if (ft_strequ(str, "rrr"))
		return (RRR);
	return (-1);
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

static t_order	add(t_order map, char *order)
{
	t_order		*new;

	new = (t_order *)malloc(sizeof(t_order));
	if (new)
	{
		new->order = strton(order);
		new->last = map.last;
		new->next = NULL;
		if (!map.next)
			map.next = new;
		if (new->last)
			new->last->next = new;
		map.last = new;
	}
	return (map);
}

/*
void			loop(t_piles p, SDL_Window *win, SDL_Renderer *render)
{
	const Uint8		*keys = SDL_GetKeyboardState(NULL);
	int				i;
	unsigned int	count;
	int				check;
	char			*str;

	p.dir = 2;
	while (!SDL_QuitRequested())
	{
		handle_key(win, keys, &(p.dir), &(p.mov));
		move(&(p.dst), &(p.mov));
		anim(&(p.src), p.dir, keys);
		ticks = SDL_GetTicks() + (1000 / FPS);
		SDL_RenderCopy(render, p.tex, &(p.src), &(p.dst));
		SDL_RenderPresent(render);
		SDL_RenderClear(render);
		while (SDL_GetTicks() < ticks);
	}
}
*/

static char		opposite(char order)
{
	if (order < 0 || order == SS)
		return (order);
	else if (order == RR || order == RRR)
		return ((order == RR) ? RRR : RR);
	else if (order <= PB)
		return ((order == PA) ? PB : PA);
	else if (order <= SB)
		return ((order == SA) ? SB : SA);
	else if (order <= RB)
		return ((order == RA) ? RB : RA);
	else
		return ((order == RRA) ? RRB : RRA);
}

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
			if (keys[SDL_SCANCODE_LEFT] && cur->last)
				cur = cur->last;
			else if (cur->next)
				cur = cur->next;
			ft_printf("%s", strinstruct((keys[SDL_SCANCODE_LEFT]) ? opposite(cur->order) : cur->order));
			apply(strinstruct((keys[SDL_SCANCODE_LEFT]) ? opposite(cur->order) : cur->order), p.p1, p.p2);
			displaystatus(p);
			SDL_Delay(1000/60);
		}
		spaced = keys[SDL_SCANCODE_SPACE];
	}
}

int				visualize(t_piles p)
{
	t_order			map;
	char			*str;
	unsigned int	count;
	int				i;
	int				check;

	count = 0;
	check = 1;
	map.next = NULL;
	map.last = NULL;
	if (init())
		return (0);
	displaystatus(p);
	while (!SDL_QuitRequested() && check && get_next_line(0, &str) > 0 && ++count)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		check = apply(str + i, p.p1, p.p2);
		map = add(map, str + i);
		displaystatus(p);
		free(str);
	}
	navigate(p, map);
	return ((!check) ? -1 : (*p.p2 == NULL && issorted(*p.p1)));
}
