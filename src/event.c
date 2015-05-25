/**********************************************
File		:event.c
Description	:callback functions for each event
Date		:2015/5/22
**********************************************/
gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data){
	printf("Click!!\n");
	if (remain_turns == 0)
		return FALSE;
	switch (event->keyval){
    	case GDK_KEY_Up:
    		printf("UP!!\n");
    		if (blank_location > 2) {
    			block_value_copy(blank_location-3, blank_location);
    			blank_location -= 3;
    			remain_turns -= 1;
    			refresh_map(blank_location+3);
    		}
    		break;
    	case GDK_KEY_Right:
    		printf("Right!!\n");
    		if (blank_location%3 < 2) {
    			block_value_copy(blank_location+1, blank_location);
    			blank_location += 1;
    			remain_turns -= 1;
    			refresh_map(blank_location-1);
    		}
    		break;
    	case GDK_KEY_Down:
    		printf("Down!!\n");
    		if (blank_location < 6) {
    			block_value_copy(blank_location+3, blank_location);
    			blank_location += 3;
    			remain_turns -= 1;
    			refresh_map(blank_location-3);
    		}
    		break;
    	case GDK_KEY_Left:
    		printf("Left!!");
    		if (blank_location%3 > 0) {
    			block_value_copy(blank_location-1, blank_location);
    			blank_location -= 1;
    			remain_turns -= 1;
    			refresh_map(blank_location+1);
    		}
    		break;
    	default:
    		printf("default!!\n");
    		break;
    }
    
	return FALSE; 
}

void block_value_copy(int source, int destination){
	int i;
	for (i = 0; i < 4; i++){
		maps[current_level].blocks[destination].dimension[i] = maps[current_level].blocks[source].dimension[i];
	}
}

gboolean refresh_map(int source){
  gtk_widget_queue_draw(window);
  mask = TRUE;
  mask_width = BLOCK_SIZE;
  mask_x = TERMINATOR_SIZE + MARGIN + (source%3)*BLOCK_SIZE;
  mask_y = TERMINATOR_SIZE + TURNS_BAR_HEIGHT + MARGIN + (source/3)*BLOCK_SIZE;
  g_timeout_add(10, (GSourceFunc) block_mask,NULL);
  return TRUE;
}

gboolean block_mask(){
	gtk_widget_queue_draw(window);
	mask_width -= 10;
	if (mask_width <= 0)
		mask = FALSE;
	return mask;
}