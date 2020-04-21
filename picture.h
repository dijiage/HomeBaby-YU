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
void drawAlpha(int x, int y, IMAGE* picture);		//͸��ͼ
void draw_store();
/*
	------����------
	-1	��¥
	0	�յ�	"./picture//diban.png"
	1	��¥	"./picture//upstairs.png"
	2	����
	3	����
	4	����
	5	ǽ
	6	����

	----------------
	------��Ʒ------
	1	��Կ��
	2	��Կ��
	3	��Կ��

	----------------
	------����------
	1	lyy
	2	����
	3	ǿ��
	4	С��

	----------------
	------����------
	1	��ɫʷ��ķ
	2	��ɫʷ��ķ
	3	��ʷ��ķ
	4	С����
	5	������
	6	��ɫ����
	7	����

	----------------
*/
