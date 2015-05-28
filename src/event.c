/**********************************************
File		:event.c
Description	:callback functions for each event
Date		:2015/5/22
**********************************************/
gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data){
	printf("%d\n", event->keyval);
	switch (event->keyval){
    	case GDK_KEY_Up:
    		printf("UP!!\n");
    		if (blank_location > 2 && !current_level_done) {
    			block_value_copy(blank_location-3, blank_location);
    			blank_location -= 3;
    			remain_turns -= 1;
    			slide_block(blank_location+3);
    		}
    		break;
    	case GDK_KEY_Right:
    		printf("Right!!\n");
    		if (blank_location%3 < 2 && !current_level_done) {
    			block_value_copy(blank_location+1, blank_location);
    			blank_location += 1;
    			remain_turns -= 1;
    			slide_block(blank_location-1);
    		}
    		break;
    	case GDK_KEY_Down:
    		printf("Down!!\n");
    		if (blank_location < 6 && !current_level_done) {
    			block_value_copy(blank_location+3, blank_location);
    			blank_location += 3;
    			remain_turns -= 1;
    			slide_block(blank_location-3);
    		}
    		break;
    	case GDK_KEY_Left:
    		printf("Left!!");
    		if (blank_location%3 > 0 && !current_level_done) {
    			block_value_copy(blank_location-1, blank_location);
    			blank_location -= 1;
    			remain_turns -= 1;
    			slide_block(blank_location+1);
    		}
    		break;
    	case GDK_KEY_space:
    		printf("space!!\n");
    		if (current_level_done){
    			next_level();
    		}
    		break;
    	default:
    		printf("default!!\n");
    		break;
    }
    if (remain_turns <= 0)
    	game_judge();
	return FALSE; 
}

void block_value_copy(int source, int destination){
	int i;
	for (i = 0; i < 4; i++){
		maps[current_level].blocks[destination].dimension[i] = maps[current_level].blocks[source].dimension[i];
	}
}

gboolean slide_block(int source){
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