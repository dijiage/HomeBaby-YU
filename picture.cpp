#include "picture.h"
#include "magictower.h"
#pragma warning(disable:4996)

extern TOWER cur_map[MAX_LAYER][13][13];
extern int mv[4][2];
extern Hero hero;
std::map<int, std::string> landID_toAddress;	//地形id对应图片地址
std::map<int, IMAGE> landID_toIMAGE;
std::map<int, std::string> itemID_toAddress;	//物品id对应图片地址
std::map<int, IMAGE> itemID_toIMAGE;
std::map<int, std::string> npcID_toAddress;		//NPC id对应图片地址
std::map<int, IMAGE> npcID_toIMAGE;
std::map<int, Monster> monsterID_toAddress;		//怪物id对应图片地址
std::map<int, IMAGE> monsterID_toIMAGE;

//加载地形素材表
void load_landID_to_Address()
{
	using namespace std;
	ifstream infile;
	infile.open("./res//land.txt");
	int No;
	string address;
	while (!infile.eof()) {
		infile >> No >> address;
		landID_toAddress.insert(pair<int, string>(No, address));
		IMAGE imp;
		loadimage(&imp, strToCString(address), 40, 40);
		landID_toIMAGE.insert(pair<int, IMAGE>(No, imp));
	}
	infile.close();
	//error_log(landID_toAddress[1]);
}

//加载物品素材表
void load_itemID_to_Address()
{
	using namespace std;
	ifstream infile;
	infile.open("./res//item.txt");
	int No;
	string address;
	while (!infile.eof()) {
		infile >> No >> address;
		itemID_toAddress.insert(pair<int, string>(No, address));
		IMAGE imp;
		loadimage(&imp, strToCString(address), 40, 40);
		itemID_toIMAGE.insert(pair<int, IMAGE>(No, imp));
	}
	infile.close();
}

//加载npc素材表
void load_npcID_to_Address()
{
	using namespace std;
	ifstream infile;
	infile.open("./res//npc.txt");
	int No;
	string address;
	while (!infile.eof()) {
		infile >> No >> address;
		npcID_toAddress.insert(pair<int, string>(No, address));
		IMAGE imp;
		loadimage(&imp, strToCString(address), 40, 40);
		npcID_toIMAGE.insert(pair<int, IMAGE>(No, imp));
	}
	infile.close();
}

//加载怪物素材表
void load_monsterID_to_Address()
{
	//未完成
	/*
	using namespace std;
	ifstream infile;
	infile.open("./res//monster.txt");
	int No;
	string address;
	while (!infile.eof()) {
		infile >> No >> address;
		monsterID_toAddress.insert(pair<int, string>(No, address));
		IMAGE imp;
		loadimage(&imp, strToCString(address), 40, 40);
		itemID_toIMAGE.insert(pair<int, IMAGE>(No, imp));
	}
	infile.close();
	*/
}

//贝叶斯公式实现easyx透明贴图	（？？？）
void drawAlpha(int x, int y, IMAGE* picture)
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标
	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

//屏幕绘制整张地图
void draw_map(int c)
{
	BeginBatchDraw();
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			drawAlpha(j * 40 + 200, i * 40, &landID_toIMAGE[cur_map[hero.layer][i][j].land]);
			drawAlpha(j * 40 + 200, i * 40, &itemID_toIMAGE[cur_map[hero.layer][i][j].item]);
			drawAlpha(j * 40 + 200, i * 40, &monsterID_toIMAGE[cur_map[hero.layer][i][j].monster]);
			drawAlpha(j * 40 + 200, i * 40, &npcID_toIMAGE[cur_map[hero.layer][i][j].npc]);
		}
	}
	IMAGE q;
	loadimage(&q, _T("./picture//yujiabao_licking_dog.png"), 40, 40);
	drawAlpha(hero.loc.x * 40 + 200, hero.loc.y * 40, &q);		//英雄初始位置
	FlushBatchDraw();
}

//屏幕绘制人物面板
void draw_data()
{
	using namespace std;
	BeginBatchDraw();
	IMAGE p;
	loadimage(&p, _T("./picture//yujiabao_silly_dog.jpg"), 200, 520);
	putimage(0, 0, &p);
	LOGFONT f;
	gettextstyle(&f);		//获取当前字体信息
	_tcscpy_s(f.lfFaceName, _T("楷体"));
	f.lfWeight = 1200;
	f.lfHeight = 30;
	f.lfWidth = 13;
	settextstyle(&f);			//设置当前字体
	settextcolor(BLACK);		//字体颜色
	setbkmode(TRANSPARENT);		//字体背景透明
	outtextxy(10, 100, _T("角色："));
	outtextxy(80, 100, strToCString(hero.name));
	outtextxy(10, 150, _T("等级："));
	outtextxy(80, 150, strToCString(to_string(hero.level)));
	outtextxy(10, 200, _T("攻："));
	outtextxy(80, 200, strToCString(to_string(hero.A)));
	outtextxy(10, 250, _T("防"));
	outtextxy(80, 250, strToCString(to_string(hero.D)));
	IMAGE imp;
	loadimage(&imp, strToCString(itemID_toAddress[1]), 40, 40);
	drawAlpha(10, 300, &imp);
	outtextxy(50, 300, _T("×"));
	outtextxy(80, 300, strToCString(to_string(hero.key[0])));
	loadimage(&imp, strToCString(itemID_toAddress[2]), 40, 40);
	drawAlpha(10, 350, &imp);
	outtextxy(50, 350, _T("×"));
	outtextxy(80, 350, strToCString(to_string(hero.key[1])));
	loadimage(&imp, strToCString(itemID_toAddress[3]), 40, 40);
	drawAlpha(10, 400, &imp);
	outtextxy(50, 400, _T("×"));
	outtextxy(80, 400, strToCString(to_string(hero.key[2])));
	FlushBatchDraw();
}

//刷新人物移动图
void draw_move(LOCAL l, int dir)
{
	BeginBatchDraw();
	IMAGE imp, imp1;
	loadimage(&imp, _T("./picture//yujiabao_licking_dog.png"), 40, 40);
	loadimage(&imp1, strToCString(landID_toAddress[cur_map[hero.layer][l.y][l.x].land]), 40, 40);
	LOCAL p = l;
	p.x += mv[dir][0];
	p.y += mv[dir][1];
	drawAlpha(p.x * 40 + 200, p.y * 40, &imp);
	putimage(l.x * 40 + 200, l.y * 40, &imp1);
	FlushBatchDraw();
}

void draw_store() {

}

