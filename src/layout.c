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
	g_signal_connect (G_OBJECT (window), "key-press-event", G_CALLBACK (on_key_press), NULL);

	draw_area = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), draw_area);
	g_signal_connect(G_OBJECT(draw_area), "draw", G_CALLBACK(on_draw_event), NULL);
	//g_signal_connect(G_OBJECT(draw_area), "expose-event",G_CALLBACK(on_draw_event), NULL);

	gtk_widget_show_all(window);

	//g_timeout_add(100, (GSourceFunc) time_handler,NULL);
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
	printf("Drawing\n");
	do_drawing(cr);
	return FALSE;
}
//It's also fucking looooooooong
void do_drawing(cairo_t *cr){
	//Background color
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_rectangle(cr, 0, 0,
			3*BLOCK_SIZE + 2*TERMINATOR_SIZE + 2*MARGIN, 
			3*BLOCK_SIZE + 2*TERMINATOR_SIZE + 2*MARGIN + TURNS_BAR_HEIGHT + MSG_BAR_HEIGHT);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);

	//Game map margin
	cairo_set_source_rgb(cr, 0.95, 0.95, 0.95);
	cairo_rectangle(cr, TERMINATOR_SIZE, TURNS_BAR_HEIGHT+TERMINATOR_SIZE, 
					3*BLOCK_SIZE + 2*MARGIN, 
					3*BLOCK_SIZE + 2*MARGIN);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);

	//game map block's background
	cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);
	cairo_rectangle(cr, TERMINATOR_SIZE+MARGIN, TURNS_BAR_HEIGHT+TERMINATOR_SIZE+MARGIN, 
					3*BLOCK_SIZE, 
					3*BLOCK_SIZE);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);

	//blank block
	cairo_set_source_rgb(cr, 0.95, 0.95, 0.95);
	cairo_rectangle(cr,
		TERMINATOR_SIZE + MARGIN + (blank_location%3)*BLOCK_SIZE, 
		TURNS_BAR_HEIGHT+TERMINATOR_SIZE+MARGIN+(blank_location/3)*BLOCK_SIZE, 
		BLOCK_SIZE, 
		BLOCK_SIZE);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);

	//Game text info
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

	//Set start point and end point  
	set_terminator(cr, maps[current_level].entry_direction, maps[current_level].entry_block);
	set_terminator(cr, maps[current_level].exit_direction, maps[current_level].exit_block);

	int i;
	cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);
	cairo_set_line_width(cr, CABLE_WIDTH);
	for (i = 0; i < 9; i++){
		int x_center = (i%3 + 0.5)*BLOCK_SIZE + TERMINATOR_SIZE + MARGIN;
		int y_center = (i/3 + 0.5)*BLOCK_SIZE + TERMINATOR_SIZE + TURNS_BAR_HEIGHT + MARGIN;
		if(i != blank_location){
			if(maps[current_level].blocks[i].dimension[0]){
				cairo_move_to(cr, x_center, y_center+0.5*CABLE_WIDTH);
				cairo_line_to(cr, x_center, y_center - 0.5*BLOCK_SIZE);
			}
			if(maps[current_level].blocks[i].dimension[1]){
				cairo_move_to(cr, x_center - 0.5*CABLE_WIDTH, y_center);
				cairo_line_to(cr, x_center + 0.5 * BLOCK_SIZE, y_center);
			}
			if(maps[current_level].blocks[i].dimension[2]){
				cairo_move_to(cr, x_center, y_center - 0.5*CABLE_WIDTH);
				cairo_line_to(cr, x_center, y_center + 0.5*BLOCK_SIZE);
			}
			if(maps[current_level].blocks[i].dimension[3]){
				cairo_move_to(cr, x_center+ 0.5*CABLE_WIDTH, y_center);
				cairo_line_to(cr, x_center - 0.5 * BLOCK_SIZE, y_center);
			}
		}
	}
	cairo_stroke_preserve(cr);

	//mask of block
	if(mask){
		cairo_set_line_width(cr, 0);
		cairo_rectangle(cr, mask_x, mask_y, mask_width, BLOCK_SIZE);
		cairo_stroke_preserve(cr);

		cairo_set_source_rgb(cr, 0.95, 0.95, 0.95);
		cairo_fill(cr);
	}
}

void set_terminator(cairo_t *cr, char direction, char block){
	int x_base = TERMINATOR_SIZE + MARGIN;
	int y_base = TERMINATOR_SIZE + TURNS_BAR_HEIGHT + MARGIN;
	cairo_set_source_rgb(cr, 0.3, 0.9, 0.3);
	switch (direction){
		case 0:
			cairo_rectangle(cr, 
				x_base + (block%3 + 0.5)*BLOCK_SIZE - 0.5*TERMINATOR_SIZE, 
				y_base-TERMINATOR_SIZE,
				TERMINATOR_SIZE,
				TERMINATOR_SIZE);	
			break;
		case 1:
			cairo_rectangle(cr, 
				x_base + 3*BLOCK_SIZE, 
				y_base + (block/3+0.5)*BLOCK_SIZE - 0.5*TERMINATOR_SIZE,
				TERMINATOR_SIZE,
				TERMINATOR_SIZE);
			break;
		case 2:
			cairo_rectangle(cr, 
				x_base + (block%3 + 0.5)*BLOCK_SIZE - 0.5*TERMINATOR_SIZE, 
				y_base + 3*BLOCK_SIZE,
				TERMINATOR_SIZE,
				TERMINATOR_SIZE);
			break;
		case 3:
			cairo_rectangle(cr, 
				x_base - TERMINATOR_SIZE, 
				y_base + (block/3+0.5)*BLOCK_SIZE - 0.5*TERMINATOR_SIZE,
				TERMINATOR_SIZE,
				TERMINATOR_SIZE);
			break;
	}
	cairo_stroke_preserve(cr);
	cairo_fill(cr);
}