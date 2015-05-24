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
		maps[level].blocks[0].top = 1;
		maps[level].blocks[0].right = 0;
		maps[level].blocks[0].bottom = 0;
		maps[level].blocks[0].left = 1;
		maps[level].blocks[1].top = 1;
		maps[level].blocks[1].right = 0;
		maps[level].blocks[1].bottom = 1;
		maps[level].blocks[1].left = 0;
		maps[level].blocks[2].top = 1;
		maps[level].blocks[2].right = 1;
		maps[level].blocks[2].bottom = 0;
		maps[level].blocks[2].left = 0;
		maps[level].blocks[3].top = 0;
		maps[level].blocks[3].right = 1;
		maps[level].blocks[3].bottom = 0;
		maps[level].blocks[3].left = 1;
		maps[level].default_blank_location = 4;
		maps[level].blocks[5].top = 0;
		maps[level].blocks[5].right = 1;
		maps[level].blocks[5].bottom = 0;
		maps[level].blocks[5].left = 1;
		maps[level].blocks[6].top = 0;
		maps[level].blocks[6].right = 0;
		maps[level].blocks[6].bottom = 1;
		maps[level].blocks[6].left = 1;
		maps[level].blocks[7].top = 0;
		maps[level].blocks[7].right = 1;
		maps[level].blocks[7].bottom = 0;
		maps[level].blocks[7].left = 1;
		maps[level].blocks[8].top = 0;
		maps[level].blocks[8].right = 1;
		maps[level].blocks[8].bottom = 1;
		maps[level].blocks[8].left = 0;
		maps[level].total_turns = 1;
		maps[level].entry_block = 3;
		maps[level].entry_direction = 3;
		maps[level].exit_block = 5;
		maps[level].exit_direction = 1;

		remain_turns = 1;
		blank_location = 4;
	}
}