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
	struct block arrang[9];
	char total_turns;
	char default_blank_location;
	char entry_block;
	char entry_direction;
	char exit_block;
	char exit_direction;
};
static struct block now_arrange[9];
static char blank_location;
static char remain_turns;

