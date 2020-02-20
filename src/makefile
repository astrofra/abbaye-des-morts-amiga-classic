.prl.gst:
	sc NOLINK CODE=F DATA=F OPTI MGST $*.gst $*.prl

.c.o:
	sc NOLINK CODE=F DATA=F OPTI TO $@ $*.c

OBJ = main.o drawing.o startscreen.o history.o game.o loading.o jean.o enemies.o ending.o gameover.o aga_sdl.o

main.exe: $(OBJ) includes.gst
	sc LINK CODE=F DATA=F OBJ $(OBJ) TO L'abbaye

includes.gst: includes.prl
main.o: main.c structs.h aga_sdl.h includes.gst
startscreen.o: startscreen.c structs.h aga_sdl.h includes.gst
history.o: history.c structs.h aga_sdl.h includes.gst
game.o: game.c structs.h aga_sdl.h game.h jean.h enemies.h drawing.h includes.gst
ending.o: ending.c structs.h aga_sdl.h includes.gst
gameover.o: gameover.c structs.h aga_sdl.h includes.gst
jean.o: jean.c structs.h aga_sdl.h includes.gst
enemies.o: enemies.c structs.h aga_sdl.h includes.gst
drawing.o: drawing.c structs.h aga_sdl.h includes.gst
aga_sdl.o: aga_sdl.c structs.h aga_sdl.h includes.gst
loading.o: loading.c structs.h aga_sdl.h includes.gst