/*  
	Wrapper that redirects a basic set of SDL functions/types
	to the graphics.library
*/

#ifndef AGA_SDL_WRAPPER
#define AGA_SDL_WRAPPER

#include <stdio.h>
#include <stdlib.h>
#include "includes.prl"

#define FRAME_BUFFER_MAX_DEPTH  6
#define FRAME_BUFFER_MAX_COLORS (2 << FRAME_BUFFER_MAX_DEPTH)

#define SDL_WINDOWPOS_CENTERED  0
#define SDL_WINDOW_OPENGL  0
#define SDL_RENDERER_PRESENTVSYNC 0
#define SDL_RENDERER_ACCELERATED 0
#define SDL_WINDOW_FULLSCREEN_DESKTOP 1
#define SDL_PIXELFORMAT_ARGB8888 0
#define SDL_TEXTUREACCESS_STATIC 0
#define SDL_HINT_RENDER_SCALE_QUALITY "HIGH"
#define MIX_DEFAULT_FORMAT 0
#define SDL_TRUE TRUE
#define SDL_FALSE FALSE 

#ifndef uint
typedef ULONG uint;
#endif

typedef BOOL SDL_bool;

typedef struct
{
  struct Screen *screen;
	struct Window *window;
  UWORD width, height;
  UBYTE db_buffer_offset;
} SDL_Window;

typedef struct
{
	SDL_Window *window;
} SDL_Renderer;

typedef struct
{
	struct BitMap *bitmap;
  int w, h;
  ULONG *palette;
} SDL_Texture;

typedef struct {
  ULONG *palette;
} SDL_PixelFormat;

typedef struct
{
  short x, y;
  UWORD w, h;
} SDL_Rect;

typedef SDL_Texture SDL_Surface;

typedef struct
{
  APTR* music_ptr;
} Mix_Music;

typedef struct {
    int allocated;
    USHORT *abuf;
    ULONG alen;
    USHORT volume;     /* Per-sample volume, 0-128 */
} Mix_Chunk;

/* Inputs */
typedef struct{
  ULONG event;
} SDL_Event;

/* Redirected SDL functions */
/* graphics */

void OpenAmigaLibraries(void);
void CloseAmigaLibraries(void);

void sleep(int t);

SDL_Window *SDL_CreateWindow(char *title, int x, int y, int w, int h, ULONG flags);
int SDL_SetWindowFullscreen(SDL_Window* window, ULONG flags);
void SDL_DestroyWindow(SDL_Window *window);

SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, ULONG flags);
SDL_bool SDL_SetHint(const char* name, const char* value);
int SDL_RenderSetLogicalSize(SDL_Renderer* renderer, int w, int h);
int SDL_SetRenderDrawColor(SDL_Renderer* renderer, USHORT r, USHORT g, USHORT b, USHORT a);
int SDL_RenderCopy(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *srcrect, SDL_Rect *dstrect);
int SDL_RenderClear(SDL_Renderer* renderer);
void SDL_RenderPresent(SDL_Renderer* renderer);
void SDL_DestroyRenderer(SDL_Renderer* renderer);

ULONG SDL_MapRGB(const SDL_PixelFormat* format, UBYTE r, UBYTE g, UBYTE b);
SDL_Surface *IMG_Load(const char *file);
int SDL_SetColorKey(SDL_Surface* surface, int flag, ULONG key);
SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);
void SDL_FreeSurface(SDL_Surface* surface);
SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, char *file);
SDL_Texture* SDL_CreateTexture(SDL_Renderer* renderer, ULONG format, int access, int w, int h);
void SDL_DestroyTexture(SDL_Texture *texture);

/* audio */
int Mix_OpenAudio(int frequency, UWORD format, int channels, int chunksize);
int Mix_AllocateChannels(int numchans);
int Mix_PlayChannel(int channel, Mix_Chunk *chunk, int loops);
Mix_Music *Mix_LoadMUS(const char *file);
int Mix_PlayMusic(Mix_Music *music, int loops);
void Mix_FreeMusic(Mix_Music *music);
int Mix_HaltMusic(void);
void Mix_ResumeMusic(void);
void Mix_FreeChunk(Mix_Chunk *chunk);
Mix_Chunk *Mix_LoadWAV(char *file);
void Mix_PauseMusic(void);

/*  Amiga AGA Specific functions */
void AGA_AppyTexturePalette(SDL_Renderer *renderer, SDL_Texture *texture);

#endif