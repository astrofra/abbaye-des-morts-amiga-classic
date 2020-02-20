/* jean.c */
#ifndef ABBAYE_JEAN
#define ABBAYE_JEAN

#include <stdio.h>
#include <stdlib.h>

#include "includes.prl"
#include "structs.h"
#include "aga_sdl.h"

void movejean (struct hero *jean, Mix_Chunk *fx[]);
void drawjean (SDL_Renderer *renderer,SDL_Texture *tiles,struct hero *jean,uint counter[],Mix_Chunk *fx[],uint changetiles);
void collisions (struct hero *jean, uint stagedata[][22][32], uint room[]);
void touchobj (struct hero *jean,uint stagedata[][22][32],uint room[],uint *parchment,uint *changeflag,struct enem *enemies,float proyec[],Mix_Chunk *fx[]);
void contact (struct hero *jean,struct enem enemies,float proyec[],uint room[]);

#endif