/* Abbaye des Morts */
/* Version 2.0 */

/* (c) 2010 - Locomalito & Gryzor87 */
/* 2013 - David "Nevat" Lara */

/* GPL v3 license */

#include <stdio.h>
#include <stdlib.h>

#include "includes.prl"

#include "structs.h"
#include "startscreen.h"
#include "history.h"
#include "game.h"
#include "gameover.h"
#include "ending.h"
#include "aga_sdl.h"

#define	MEGADRIVE_GRAPHIC_SET

main () {

	uint exit = 0;
	uint state = 0; /* 0-intro,1-history,2-game */
	uint grapset = 1; /* 0-8bits, 1-16bits */
	uint fullscreen = 0; /* 0-Windowed,1-Fullscreen */
	SDL_Window *screen;

	OpenAmigaLibraries();

	/* Creating window */
	screen = SDL_CreateWindow("Abbaye des Morts v2.0",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,256,192,SDL_WINDOW_OPENGL);

	/* Init audio */
	Mix_OpenAudio (44100,MIX_DEFAULT_FORMAT,2,4096);
	Mix_AllocateChannels(5);

state = 1;

	while (exit != 1) {
		switch (state) {
			case 0: startscreen(screen,&state,&grapset,&fullscreen);
							break;
			case 1: history(screen,&state,&grapset,&fullscreen);
							break;
			case 2: game(screen,&state,&grapset,&fullscreen);
							break;
			case 3: gameover(screen,&state);
							break;
			case 4: ending(screen,&state);
							break;
			case 6: exit = 1;
							break;
		}

		exit = 1;
	}

	/* Cleaning */
	SDL_DestroyWindow(screen);

	CloseAmigaLibraries();
	/* Exiting normally */
	return 0;

}