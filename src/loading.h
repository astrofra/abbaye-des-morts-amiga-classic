/* loading.c */
#ifndef ABBAYE_LOADING
#define ABBAYE_LOADING

#include <stdio.h>
#include <stdlib.h>

#include "includes.prl"
#include "structs.h"
#include "aga_sdl.h"

void loaddata(uint stagedata[][22][32],int enemydata[][7][15]);
void loadingmusic(Mix_Music *bso[], Mix_Chunk *fx[]);

#endif