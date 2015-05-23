/***************************************
File		:layout.c
Description	:arrange each static widget
Date		:2015/5/22
***************************************/
GtkWidget *window;
void layout_init(){
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Power Engineer");
	gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, WIDTH+TURNS_BAR_HEIGHT+MSG_BAR_HEIGHT);
	gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("img/window_icon.png"));
	g_signal_connect(G_OBJECT(window), "delete_event",gtk_main_quit, NULL);


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

