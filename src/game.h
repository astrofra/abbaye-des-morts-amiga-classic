/* game.c */
#ifndef ABBAYE_GAME
#define ABBAYE_GAME

#include <stdio.h>
#include <stdlib.h>

#include "includes.prl"
#include "structs.h"
#include "aga_sdl.h"

void keybpause (uint *keyp);
void music (uint room[], Mix_Music *bso[],uint *changeflag,int flag);
void changescreen (struct hero *jean,uint room[],uint *changeflag);
void events (struct hero *jean,uint stagedata[][22][32],uint room[],uint counter[],struct enem *enemies,Mix_Chunk *fx[]);
void control (struct hero *jean,uint *keyp);
void counters (uint counter[]);
void animation (uint stagedata[][22][32], uint room[], uint counter[]);
void game(SDL_Window *screen,uint *state,uint *grapset,uint *fullscreen);

#endif