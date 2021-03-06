#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "property.c"
#include "interface.c"
#include "control.c"
#include "layout.c"
#include "event.c"
#include "animation.c"

int main(int argc, char *argv[]){
	gtk_init(&argc, &argv);
	game_init();
	layout_init();
	gtk_main();
	return 0;
}