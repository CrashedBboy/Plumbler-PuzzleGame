/***************************************
File		:property.c
Description	:game parameter and constant
Date		:2015/5/22
***************************************/
struct block{
	char top;
	char right;
	char bottom;
	char left;
};
struct map{
	struct block blocks[9];
	char total_turns;
	char default_blank_location;
	char entry_block;
	char entry_direction;
	char exit_block;
	char exit_direction;
};
static struct map maps[2];
static char blank_location;
static int remain_turns;
static int current_level = 0;
static char remain_str[5];
static char level_str[5];

static int MARGIN = 12;
static int TERMINATOR_SIZE = 30;
static int BLOCK_SIZE = 120;
static int CABLE_WIDTH = 30;
static int TURNS_BAR_HEIGHT = 70;
static int MSG_BAR_HEIGHT = 70;

