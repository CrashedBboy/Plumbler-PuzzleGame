/***************************************
File		:interface.c
Description	:Define function interfaces 
Date		:2015/5/22
***************************************/
void layout_init();
GdkPixbuf *create_pixbuf(const gchar*);
gboolean on_draw_event(GtkWidget*, cairo_t*, gpointer);
void do_drawing(cairo_t*);
void set_terminator(cairo_t*, int, int);

void set_map_level(int);
void game_judge();
void next_level();

gboolean on_key_press(GtkWidget*, GdkEventKey*, gpointer);
void block_value_copy(int, int);


gboolean slide_block(int);
gboolean block_mask();
