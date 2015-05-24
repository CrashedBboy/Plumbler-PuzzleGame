#include <stdio.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include "property.c"
#include "interface.c"
#include "control.c"
#include "layout.c"
#include "event.c"
#include "animation.c"

int main(int argc, char *argv[]){
	printf("Hello Power Engineer!\n");
	gtk_init(&argc, &argv);
	game_init();
	layout_init();
	gtk_main();
	return 0;
}