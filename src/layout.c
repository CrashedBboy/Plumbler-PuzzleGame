/***************************************
File		:layout.c
Description	:arrange each static widget
Date		:2015/5/22
***************************************/
GtkWidget *window;
GtkWidget *draw_area;
void layout_init(){
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Power Engineer");
	gtk_window_set_default_size(GTK_WINDOW(window), 
			3*BLOCK_SIZE + 2*TERMINATOR_SIZE + 2*MARGIN, 
			3*BLOCK_SIZE + 2*TERMINATOR_SIZE + 2*MARGIN + TURNS_BAR_HEIGHT + MSG_BAR_HEIGHT);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("img/window_icon.png"));
	gtk_window_set_has_resize_grip(GTK_WINDOW(window), FALSE);
	g_signal_connect(G_OBJECT(window), "delete_event",gtk_main_quit, NULL);

	draw_area = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), draw_area);
	g_signal_connect(G_OBJECT(draw_area), "draw", G_CALLBACK(on_draw_event), NULL);

	gtk_widget_show_all(window);
}
GdkPixbuf *create_pixbuf(const gchar *filename){
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   if(!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }
   return pixbuf;
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data){
	do_drawing(cr);
	return FALSE;
}

void do_drawing(cairo_t *cr){
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_rectangle(cr, 0, 0,
			3*BLOCK_SIZE + 2*TERMINATOR_SIZE + 2*MARGIN, 
			3*BLOCK_SIZE + 2*TERMINATOR_SIZE + 2*MARGIN + TURNS_BAR_HEIGHT + MSG_BAR_HEIGHT);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);

	cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);
	cairo_rectangle(cr, TERMINATOR_SIZE, TURNS_BAR_HEIGHT+TERMINATOR_SIZE, 
					3*BLOCK_SIZE + 2*MARGIN, 
					3*BLOCK_SIZE + 2*MARGIN);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);

	cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
	cairo_set_font_size(cr,25);
	cairo_move_to(cr, 30, 50);
	cairo_show_text(cr, "Remain Turns:");
	cairo_move_to(cr, 320, 50);
	cairo_show_text(cr, "Level ");
	cairo_stroke_preserve(cr);
	cairo_set_font_size(cr, 20);
	cairo_move_to(cr, 90, 540);
	cairo_show_text(cr, "TIPS: Use the arrow keys");
	cairo_stroke_preserve(cr);

	cairo_set_source_rgb(cr, 0.4, 0.9, 0.4);
	cairo_set_font_size(cr,25);
	cairo_move_to(cr, 220, 50);
	sprintf(remain_str, "%d", remain_turns);
	cairo_show_text(cr, remain_str);
	cairo_move_to(cr, 390, 50);
	sprintf(level_str, "%d", current_level);
	cairo_show_text(cr, level_str);
	cairo_stroke_preserve(cr);

	//cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
	//cairo_set_line_width(cr, 5);
	//cairo_move_to(cr, 0, 0);
	//cairo_line_to(cr, 200, 100);
	//cairo_stroke_preserve(cr);
}
