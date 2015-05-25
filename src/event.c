/**********************************************
File		:event.c
Description	:callback functions for each event
Date		:2015/5/22
**********************************************/
gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data){
	if (remain_turns == 0)
		return FALSE;
	switch (event->keyval){
    	case GDK_KEY_uparrow:
    		if (blank_location > 2) {
    			block_value_copy(blank_location-3, blank_location);
    			blank_location -= 3;
    			remain_turns -= 1;
    		}
    		break;
    	case GDK_KEY_rightarrow:
    		break;
    	case GDK_KEY_downarrow:
    		if (blank_location < 6) {
    			block_value_copy(blank_location+3, blank_location);
    			blank_location += 3;
    			remain_turns -= 1;
    		}
    		break;
    	case GDK_KEY_leftarrow:
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