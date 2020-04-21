#include "magictower.h"
#include "picture.h"
#pragma warning(disable:4996)

int mv[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };
TOWER cur_map[MAX_LAYER][Height][Width];
extern Hero hero;

//调试输出错误信息
void error_log(int a)
{
	std::ofstream outfile;
	outfile.open("./error.txt", std::ios::app);
	outfile << a << std::endl;
}
void error_log(std::string str)
{
	std::ofstream outfile;
	outfile.open("./error.txt", std::ios::app);
	outfile << str << std::endl;
}
void error_log(char* p)
{
	std::ofstream outfile;
	outfile.open("./error.txt", std::ios::app);
	std::string tmp = p;
	outfile << tmp << std::endl;
}

//加载地图数据
void load_map_data()
{
	std::ifstream infile;
	for (int k = 1; k < MAX_LAYER; k++) {
		char p[20] = "./map//L";
		p[8] = k + '0';
		strcpy((p + 9), ".txt");
		infile.open(p);
		if (!infile.is_open()) {
			error_log("gg");
			return;
		}
		//加载地图
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				infile >> cur_map[k][i][j].land;
			}
		}
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				infile >> cur_map[k][i][j].item;
			}
		}
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				infile >> cur_map[k][i][j].monster;
			}
		}
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				infile >> cur_map[k][i][j].npc;
			}
		}
		infile.close();
	}
}

//初始化地图
void init_map()
{
	initgraph(960, 520);
	load_landID_to_Address();
	load_itemID_to_Address();
	load_monsterID_to_Address();
	load_npcID_to_Address();
	load_map_data();
	//加载地图图像
	draw_map(hero.layer);
	//加载角色信息
	draw_data();
}

void go()
{
	while (1) {
		if (_kbhit()) {
			int ch;
			ch = _getch();
			switch (ch)
			{
			case 72: {
				hero.go_up();
				break;
			}
			case 80: {
				hero.go_down();
				break;
			}
			case 75: {
				hero.go_left();
				break;
			}
			case 77: {
				hero.go_right();
				break;
			}
			default:
				break;
			}
		}
	}
}

//好像没啥用
void Hero::get_loc(const int _cur_map[][Width])
{
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			if (_cur_map[i][j] == 1) {
				this->loc.x = i;
				this->loc.y = j;
				return;
			}
		}
	}
}

//判断下一步能不能走
bool can_go(LOCAL c)
{
	int t = cur_map[hero.layer][c.y][c.x].land;
	if (c.x < 0 || c.x >= Width || c.y < 0 || c.y >= Height) {
		return false;
	}
	if (t == 0 || t == 1 || t == -1) {
		return true;
	}
	if (t == 2 || t == 3 || t == 4) {
		if (hero.key[t - 2]) {
			return true;
		}
	}
	return false;
}

//事件判断
void judge_event(LOCAL c, int dir)
{
	LOCAL next = c;
	next.x += mv[dir][0];
	next.y += mv[dir][1];
	hero.loc = next;

	//地形
	switch (cur_map[hero.layer][next.y][next.x].land) {
	case -1:
		draw_move(c, dir);
		hero.layer--;
		draw_map(hero.layer);
		draw_data();
		break;
	//空地
	case 0:
		draw_move(c, dir);
		break;
	//上楼
	case 1: {
		draw_move(c, dir);
		hero.layer++;
		draw_map(hero.layer);
		draw_data();
		break;
	}
	//黄门
	case 2:
		hero.loc = c;
		hero.key[0]--;
		cur_map[hero.layer][next.y][next.x].land = 0;
		draw_map(hero.layer);
		draw_data();
		break;
	//蓝门
	case 3:
		hero.loc = c;
		hero.key[1]--;
		cur_map[hero.layer][next.y][next.x].land = 0;
		draw_map(hero.layer);
		draw_data();
		break;
	//红门
	case 4:
		hero.loc = c;
		hero.key[2]--;
		cur_map[hero.layer][next.y][next.x].land = 0;
		draw_map(hero.layer);
		draw_data();
		break;
	default:
		break;
	}

	//物品
	switch (cur_map[hero.layer][next.y][next.x].item) {
	//黄钥匙
	case 1:
		hero.key[0]++;
		cur_map[hero.layer][next.y][next.x].item = 0;
		draw_map(hero.layer);
		draw_data();
		break;
	//蓝钥匙
	case 2:
		hero.key[1]++;
		cur_map[hero.layer][next.y][next.x].item = 0;
		draw_map(hero.layer);
		draw_data();
		break;
	//红钥匙
	case 3:
		hero.key[2]++;
		cur_map[hero.layer][next.y][next.x].item = 0;
		draw_map(hero.layer);
		draw_data();
		break;
	default:
		break;
	}

	//npc
	switch (cur_map[hero.layer][next.y][next.x].npc) {
	case 1:
		open_store();
	}
}

void Hero::go_up() {
	LOCAL next = this->loc;
	next.x += mv[0][0];
	next.y += mv[0][1];
	if (can_go(next)) {
		judge_event(this->loc, 0);
	}
}

void Hero::go_down() {
	LOCAL next = this->loc;
	next.x += mv[1][0];
	next.y += mv[1][1];
	if (can_go(next)) {
		judge_event(this->loc, 1);
	}
}

void Hero::go_left() {
	LOCAL next = this->loc;
	next.x += mv[2][0];
	next.y += mv[2][1];
	if (can_go(next)) {
		judge_event(this->loc, 2);
	}
}

void Hero::go_right() {
	LOCAL next = this->loc;
	next.x += mv[3][0];
	next.y += mv[3][1];
	if (can_go(next)) {
		judge_event(this->loc, 3);
	}
}

//string转_T()
CString strToCString(std::string str) {
	CString str1 = str.c_str();
	return str1;
}

void open_store() {
	draw_store();
}


