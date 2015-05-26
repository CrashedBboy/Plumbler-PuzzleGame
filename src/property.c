/***************************************
File		:property.c
Description	:game parameter and constant
Date		:2015/5/22
***************************************/
struct block{
	int dimension[4];
};
struct map{
	struct block blocks[9];
	int total_turns;
	int default_blank_location;
	int entry_block;
	int entry_direction;
	int exit_block;
	int exit_direction;
};
static struct map maps[1];
static int blank_location;
static int remain_turns;
static int current_level = 0;
static char remain_str[5];
static char level_str[5];
static gboolean mask = FALSE;
static gboolean current_level_done = FALSE;
static int mask_x;
static int mask_y;
static int mask_width;

static int MARGIN = 12;
static int TERMINATOR_SIZE = 30;
static int BLOCK_SIZE = 120;
static int CABLE_WIDTH = 20;
static int TURNS_BAR_HEIGHT = 70;
static int MSG_BAR_HEIGHT = 70;

