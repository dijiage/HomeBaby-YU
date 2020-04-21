#include <string>
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include <cstring>
#include <atlstr.h>

//长宽格数
#define Height 13		
#define Width 13
//塔的层数
#define MAX_LAYER 4


struct LOCAL {
	//坐标
	int x, y;
};

class Hero {
public:
	std::string name;
	LOCAL loc;
	int HP;
	int money;
	int layer;
	int level;
	int A;
	int D;
	int key[5] = { 0 };
	void go_up();
	void go_down();
	void go_left();
	void go_right();
	void get_loc(const int _cur_map[][Width]);
	Hero() {
		this->name = "于家宝";
		this->HP = 1000;
		this->money = 0;
		for (int i = 0; i < 5; i++) {
			key[i] = 0;
		}
		this->A = this->D = 10;
		this->level = this->layer = 1;
		this->loc.x = 6;
		this->loc.y = 12;
	}
};

class Monster {
public:
	int ID;
	std::string name;
	CString address;
	int HP;
	int A;
	int D;
	int money;
	int exp;
	bool operator < (const Monster p)const {
		return this->name < p.name;
	}
};

struct TOWER {
	int land;		//地形
	int item;		//资源物品
	int npc;
	int monster;	//怪物种类
};


void init_map();		//地图初始化
void go();		//游戏开始
bool can_go(LOCAL c);	//判断能不能走
void judge_event(LOCAL c, int dir);	//判定事件发生
void error_log(std::string str);
void error_log(int a);
void error_log(char* p);
void load_map_data();
void open_store();
CString strToCString(std::string str);

