/*  
	Wrapper that redirects a basic set of SDL functions/types
	to the graphics.library
*/

#include <stdio.h>
#include <stdlib.h>
#include "includes.prl"
#include "aga_sdl.h"

struct Library *IntuitionBase;
struct Library *GfxBase;
struct Library *DataTypesBase;

/* Redirected SDL functions */
/* graphics */
void sleep(int t) { }

void OpenAmigaLibraries()
{
  IntuitionBase = OpenLibrary("intuition.library", 36L);
  GfxBase = OpenLibrary("graphics.library", 36L);
  DataTypesBase = OpenLibrary("datatypes.library",0L);
}

void CloseAmigaLibraries()
{
  CloseLibrary(DataTypesBase);
  CloseLibrary(GfxBase);
  CloseLibrary(IntuitionBase);
}

SDL_Window *SDL_CreateWindow(char *title, int x, int y, int w, int h, ULONG flags)
{
  SDL_Window *new_window;
  new_window = (SDL_Window *)malloc(sizeof(SDL_Window));
  memset(new_window, 0, sizeof(SDL_Window));

  new_window->screen = OpenScreenTags(NULL,
                SA_Width, w,
                SA_Height, h * 2,
                SA_Depth, FRAME_BUFFER_MAX_DEPTH,
                SA_DisplayID, 0,
                TAG_DONE);

  new_window->width = w;
  new_window->height = h;

  //printf("%s : SDL_CreateWindow()\n", __FILE__);
  //printf("new_window->screen = %x\n", new_window->screen);
  /* Open window */
  return new_window;
}

int SDL_SetWindowFullscreen(SDL_Window* window, ULONG flags)
{
  return 1;
}

void SDL_DestroyWindow(SDL_Window *window)
{
  //printf("%s : SDL_DestroyWindow()\n", __FILE__);
  CloseScreen(window->screen);
  free(window);
  window = NULL;
}

SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, ULONG flags)
{
  SDL_Renderer *new_render;
  new_render = (SDL_Renderer *)malloc(sizeof(SDL_Renderer));
  new_render->window = window;

  return new_render;
}

SDL_bool SDL_SetHint(const char* name, const char* value)
{
  return TRUE;
}

int SDL_RenderSetLogicalSize(SDL_Renderer* renderer, int w, int h)
{
  return 1;
}

int SDL_SetRenderDrawColor(SDL_Renderer* renderer, USHORT r, USHORT g, USHORT b, USHORT a)
{
  return 1;

}

int SDL_RenderCopy(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *srcrect, SDL_Rect *dstrect)
{
  // short dw, dh;

  //printf("%s : SDL_RenderCopy()\n", __FILE__);

  // if (dstrect->x > renderer->window->width || dstrect->y > renderer->window->height)
  //   return 0;

  // if (dstrect->x + dstrect->w > renderer->window->width)
  // {
  //   dw = dstrect->w - (renderer->window->width - (dstrect->x + dstrect->w));
  //   if (dw <= 0)
  //     return 0;
  //   dstrect->w = dw;
  // }

  // if (dstrect->y + dstrect->h > renderer->window->height)
  // {
  //   dh = dstrect->h - (renderer->window->height - (dstrect->y + dstrect->h));
  //   if (dh <= 0)
  //     return 0;
  //   dstrect->h = dh;
  // }

  BltBitMap(texture->bitmap, srcrect->x, srcrect->y,
    renderer->window->screen->RastPort.BitMap, dstrect->x, dstrect->y + renderer->window->db_buffer_offset,
    dstrect->w, dstrect->h,
    0xC0, 0xFF, NULL);

  return 1;
}

void AGA_AppyTexturePalette(SDL_Renderer *renderer, SDL_Texture *texture)
{
  UWORD i;
  ULONG r,g,b;

  //printf("%s : AGA_AppyTexturePalette(), %d colors.\n", __FILE__, texture->palette[0]);

  if (texture->palette[0] > 0)
  {
    for(i=0; i < texture->palette[0]; i++ )
    {
      r = texture->palette[i * 3 + 1];
      g = texture->palette[i * 3 + 2];
      b = texture->palette[i * 3 + 3];
      // //printf("Color%d = (%x,%x,%x),", i, r, g, b);
      SetRGB32(&(renderer->window->screen->ViewPort), i, r, g, b);
    }
  }
}

int SDL_RenderClear(SDL_Renderer* renderer)
{
  // SetRast(&(renderer->window->screen->RastPort), 0);
  SetAPen(&(renderer->window->screen->RastPort), 0);
  RectFill(&(renderer->window->screen->RastPort), 
            0, renderer->window->db_buffer_offset, 
            renderer->window->width - 1, renderer->window->height + renderer->window->db_buffer_offset - 1);  
  return 1;
}

void SDL_RenderPresent(SDL_Renderer* renderer)
{
  renderer->window->screen->ViewPort.RasInfo->RyOffset = renderer->window->db_buffer_offset;
  ScrollVPort(&(renderer->window->screen->ViewPort));

  if (renderer->window->db_buffer_offset == 0)
    renderer->window->db_buffer_offset = renderer->window->height;
  else
    renderer->window->db_buffer_offset = 0;
}

/*
  SDL_DestroyRenderer
*/
void SDL_DestroyRenderer(SDL_Renderer* renderer)
{
  if (renderer != NULL)
    free(renderer);
  renderer = NULL;
}

ULONG SDL_MapRGB(const SDL_PixelFormat* format, UBYTE r, UBYTE g, UBYTE b)
{
  return 1;
}

SDL_Surface *IMG_Load(const char *file)
{
  return NULL;
}

int SDL_SetColorKey(SDL_Surface* surface, int flag, ULONG key)
{
  return 1;
}

SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface)
{
  return (SDL_Texture *)surface;
}

/*
  SDL_FreeSurface
*/
void SDL_FreeSurface(SDL_Surface* surface)
{
  if (surface != NULL)
  {
    if (surface->bitmap != NULL)
      FreeBitMap(surface->bitmap);

    free(surface);
    surface = NULL;
  }
}

/*
  IMG_LoadTexture
*/
SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, char *file)
{
  SDL_Texture *new_texture = NULL;
  APTR dtobject = NULL;
  ULONG *cregs = NULL;
  ULONG modeID = INVALID_ID;
  struct dtFrameBox mydtFrameBox;
  struct FrameInfo myFrameInfo;
  struct gpLayout mygpLayout;
  ULONG res;
  UWORD numcolors, i, j;
  ULONG r,g,b;

  //printf("%s : IMG_LoadTexture(%s)\n", __FILE__, file);

  new_texture = (SDL_Texture *)malloc(sizeof(SDL_Texture));
  memset(new_texture, 0, sizeof(SDL_Texture));
 
  dtobject = NewDTObject(file, PDTA_Remap, FALSE, DTA_GroupID, GID_PICTURE, TAG_END);

  mydtFrameBox.MethodID         = DTM_FRAMEBOX;
  mydtFrameBox.dtf_GInfo        = NULL;
  mydtFrameBox.dtf_ContentsInfo = NULL;
  mydtFrameBox.dtf_FrameInfo    = &myFrameInfo;
  mydtFrameBox.dtf_SizeFrameInfo= sizeof (struct FrameInfo);
  mydtFrameBox.dtf_FrameFlags   = 0L;

  res = DoMethodA(dtobject, (Msg)&mydtFrameBox);

  //printf("Texture specs : w = %d, h = %d, d = %d\n", myFrameInfo.fri_Dimensions.Width, myFrameInfo.fri_Dimensions.Height, myFrameInfo.fri_Dimensions.Depth);

  mygpLayout.MethodID   = DTM_PROCLAYOUT;
  mygpLayout.gpl_GInfo  = NULL;
  mygpLayout.gpl_Initial= 1L;

  res = DoMethodA(dtobject, (Msg)&mygpLayout);
  res = GetDTAttrs(dtobject, PDTA_ModeID, &modeID, PDTA_CRegs, &cregs, PDTA_BitMap, &(new_texture->bitmap), TAG_END);

  numcolors = 2<<(myFrameInfo.fri_Dimensions.Depth-1);
  new_texture->palette = (ULONG *)malloc(sizeof(ULONG) * (numcolors * 3 + 2));

  new_texture->palette[0] = numcolors;

  for( i=0, j=0; i < numcolors; i++ )
  {
    r = cregs[i * 3 + 0];
    g = cregs[i * 3 + 1];
    b = cregs[i * 3 + 2];
    new_texture->palette[++j] = r;
    new_texture->palette[++j] = g;
    new_texture->palette[++j] = b;
    // //printf("Color%d = (%x,%x,%x),", i, r, g, b);
  }

  new_texture->palette[j] = 0;
  // DisposeDTObject(dtobject);

  return new_texture;
}

/*
  SDL_CreateTexture
*/
SDL_Texture* SDL_CreateTexture(SDL_Renderer* renderer, ULONG format, int access, int w, int h)
{
  SDL_Texture *new_texture;
  new_texture = (SDL_Texture *)malloc(sizeof(SDL_Texture));
  memset(new_texture, 0, sizeof(SDL_Texture));
  new_texture->bitmap = AllocBitMap(w,h,renderer->window->screen->RastPort.BitMap->Depth, BMF_DISPLAYABLE, NULL);
  return new_texture;
}

/*
  SDL_DestroyTexture
*/
void SDL_DestroyTexture(SDL_Texture *texture)
{
  if (texture != NULL)
  {
    if (texture->bitmap != NULL)
      FreeBitMap(texture->bitmap);
    if (texture->palette != NULL)
      free(texture->palette);
    free(texture);
    texture = NULL;
  }
}

/* audio */
int Mix_OpenAudio(int frequency, UWORD format, int channels, int chunksize)
{
  return 1;
}

int Mix_AllocateChannels(int numchans)
{
  return 1;
}

int Mix_PlayChannel(int channel, Mix_Chunk *chunk, int loops)
{
  return 1;
}

Mix_Music *Mix_LoadMUS(const char *file)
{
  return NULL;
}

int Mix_PlayMusic(Mix_Music *music, int loops)
{
  return 1;
}

void Mix_FreeMusic(Mix_Music *music){ }

int Mix_HaltMusic(void)
{ 
  return 1; 
}

void Mix_ResumeMusic(void) { }

void Mix_FreeChunk(Mix_Chunk *chunk) { }

Mix_Chunk *Mix_LoadWAV(char *file)
{ 
  return NULL;
}

void Mix_PauseMusic(void) { }
