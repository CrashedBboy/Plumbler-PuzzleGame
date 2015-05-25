/*****************************************
File		:control.c
Description	:COntrol the whole game's flow
Date		:2015/5/22
*****************************************/
void game_init(){
	set_map_level(current_level);
}

/*Is there a simple way? It's fuckig looooooooooooong*/
void set_map_level(int level){
	if (level == 0){
		maps[level].blocks[0].dimension[0] = 1;
		maps[level].blocks[0].dimension[1] = 0;
		maps[level].blocks[0].dimension[2] = 0;
		maps[level].blocks[0].dimension[3] = 1;
		maps[level].blocks[1].dimension[0] = 1;
		maps[level].blocks[1].dimension[1] = 0;
		maps[level].blocks[1].dimension[2] = 1;
		maps[level].blocks[1].dimension[3] = 0;
		maps[level].blocks[2].dimension[0] = 1;
		maps[level].blocks[2].dimension[1] = 1;
		maps[level].blocks[2].dimension[2] = 0;
		maps[level].blocks[2].dimension[3] = 0;
		maps[level].blocks[3].dimension[0] = 0;
		maps[level].blocks[3].dimension[1] = 1;
		maps[level].blocks[3].dimension[2] = 0;
		maps[level].blocks[3].dimension[3] = 1;
		maps[level].default_blank_location = 4;
		maps[level].blocks[5].dimension[0] = 0;
		maps[level].blocks[5].dimension[1] = 1;
		maps[level].blocks[5].dimension[2] = 0;
		maps[level].blocks[5].dimension[3] = 1;
		maps[level].blocks[6].dimension[0] = 0;
		maps[level].blocks[6].dimension[1] = 0;
		maps[level].blocks[6].dimension[2] = 1;
		maps[level].blocks[6].dimension[3] = 1;
		maps[level].blocks[7].dimension[0] = 0;
		maps[level].blocks[7].dimension[1] = 1;
		maps[level].blocks[7].dimension[2] = 0;
		maps[level].blocks[7].dimension[3] = 1;
		maps[level].blocks[8].dimension[0] = 0;
		maps[level].blocks[8].dimension[1] = 1;
		maps[level].blocks[8].dimension[2] = 1;
		maps[level].blocks[8].dimension[3] = 0;
		maps[level].total_turns = 1;
		maps[level].entry_block = 3;
		maps[level].entry_direction = 3;
		maps[level].exit_block = 5;
		maps[level].exit_direction = 1;

		remain_turns = 1;
		blank_location = 4;
	}
}