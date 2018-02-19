/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 23:49:29 by ygaude            #+#    #+#             */
/*   Updated: 2018/02/19 23:27:22 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# define WIN_W 1920
# define WIN_H 1080

typedef struct			s_winenv
{
	SDL_Rect			dst;
	SDL_Rect			src;
	SDL_Texture			*tex;
	SDL_Texture			*canvas;
	SDL_Window			*win;
	SDL_Renderer		*render;
	Uint32				visuticks;
	Uint32				ticks;
	Uint32				delay;
	unsigned int		max;
	int					pop;
	int					autoplay;
	int					quit;
}						t_winenv;

void					displaystatus(t_piles p);
int						events(t_winenv *env);
unsigned int			maxvalue(t_pile *p, int *pop);
t_winenv				*getsdlenv(t_pile *p);
int						init(void);
int						issorted(t_pile *pile);

#endif
