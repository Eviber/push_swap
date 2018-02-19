/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 23:49:29 by ygaude            #+#    #+#             */
/*   Updated: 2018/02/17 09:29:35 by ygaude           ###   ########.fr       */
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
	unsigned int		max;
	int					pop;
}						t_winenv;

unsigned int			maxvalue(t_pile *p, int *pop);
t_winenv				*getsdlenv(t_pile *p);
int						init(void);
int						issorted(t_pile *pile);

#endif
