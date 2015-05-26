/*****************************************
File		:control.c
Description	:COntrol the whole game's flow
Date		:2015/5/22
*****************************************/
void game_init(){
	FILE *map_info;
	int total_levels;
	map_info= fopen("map.info", "r");
	fscanf(map_info, "%d\n",&total_levels);
	int i;
	for(i = 0; i < total_levels; i++){
		fscanf(map_info, "%d\n", &maps[i].total_turns);
		fscanf(map_info, "%d\n", &maps[i].default_blank_location);
		fscanf(map_info, "%d\n", &maps[i].entry_block);
		fscanf(map_info, "%d\n", &maps[i].entry_direction);
		fscanf(map_info, "%d\n", &maps[i].exit_block);
		fscanf(map_info, "%d\n", &maps[i].exit_direction);
		int j;
		for (j = 0; j < 9; j++){
			if (j != maps[i].default_blank_location)
				fscanf(map_info, "%d %d %d %d\n", 
					&maps[i].blocks[j].dimension[0],
					&maps[i].blocks[j].dimension[1],
					&maps[i].blocks[j].dimension[2],
					&maps[i].blocks[j].dimension[3]);
		}
	}
	set_map_level(current_level);
}

/*Is there a simple way? It's fuckig looooooooooooong*/
void set_map_level(int level){
		remain_turns = maps[level].total_turns;
		blank_location = maps[level].default_blank_location;
		mask = FALSE;
		current_level_done = FALSE;
}

void game_judge(){

}
