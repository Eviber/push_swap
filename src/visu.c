/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 06:57:16 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/26 10:16:50 by ygaude           ###   ########.fr       */
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

static void		clear(t_winenv *env)
{
	SDL_Rect	rect;

	rect.w = WIN_W / 2;
	rect.h = WIN_H;
	rect.x = 0;
	rect.y = 0;
	SDL_SetRenderDrawColor(env->render, 150, 150, 200, 0);
	SDL_RenderDrawRect(env->render, &rect);
	rect.x = WIN_W / 2;
	rect.y = 0;
	rect.w = WIN_W / 2;
	rect.h = WIN_H;
	SDL_SetRenderDrawColor(env->render, 200, 150, 150, 0);
	SDL_RenderDrawRect(env->render, &rect);
}

static void		displaystatus(t_winenv *env, t_piles p)
{
//	SDL_Rect		rect;
	//t_pile			*cur;

	clear(env);
	if (!p == 200000)
		;
	//rect.w = WIN_W / (widest(p) * 2);
	SDL_RenderPresent(env->render);
//	SDL_SetRenderDrawColor(env->render, 255, 0, 0, 0);
//	SDL_RenderClear(env->render);
}

static char		strton(char *str)
{
	if (ft_strequ(str, "pa"))
		return (PA);
	if (ft_strequ(str, "pb"))
		return (PA);
	if (ft_strequ(str, "sa"))
		return (PA);
	if (ft_strequ(str, "sb"))
		return (PA);
	if (ft_strequ(str, "ss"))
		return (PA);
	if (ft_strequ(str, "ra"))
		return (PA);
	if (ft_strequ(str, "rb"))
		return (PA);
	if (ft_strequ(str, "rr"))
		return (PA);
	if (ft_strequ(str, "rra"))
		return (PA);
	if (ft_strequ(str, "rrb"))
		return (PA);
	if (ft_strequ(str, "rrr"))
		return (PA);
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
	}
	return (map);
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
	displaystatus(getsdlenv(), p);
	while (check && get_next_line(0, &str) > 0 && ++count)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		check = apply(str + i, p.p1, p.p2);
		map = add(map, str + i);
		displaystatus(getsdlenv(), p);
		free(str);
	}
	return ((!check) ? -1 : (*p.p2 == NULL && issorted(*p.p1)));
}
