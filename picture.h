#include <graphics.h>
#include <conio.h>
#include <Windows.h>
#include <atlstr.h>

class Hero;
struct LOCAL;



void draw_map(int c);
void draw_data();
void draw_move(LOCAL l, int dir);
void load_landID_to_Address();
void load_itemID_to_Address();
void load_npcID_to_Address();
void load_monsterID_to_Address();
void drawAlpha(int x, int y, IMAGE* picture);		//透明图
void draw_store();
/*
	------地形------
	-1	下楼
	0	空地	"./picture//diban.png"
	1	上楼	"./picture//upstairs.png"
	2	黄门
	3	蓝门
	4	红门
	5	墙
	6	铁门

	----------------
	------物品------
	1	黄钥匙
	2	蓝钥匙
	3	红钥匙

	----------------
	------人物------
	1	lyy
	2	商人
	3	强龙
	4	小敏

	----------------
	------怪物------
	1	绿色史莱姆
	2	红色史莱姆
	3	大史莱姆
	4	小蝙蝠
	5	大蝙蝠
	6	红色蝙蝠
	7	兽人

	----------------
*/
